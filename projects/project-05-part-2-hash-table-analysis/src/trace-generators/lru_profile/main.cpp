#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <list>
#include <unordered_map>

#include "../../../utils/TraceConfig.hpp"

const char* WORDS_FILE = "20980712_uniq_words.txt";

// -----------------------------------------------------------------------------
// Load words:
// -----------------------------------------------------------------------------
std::vector<std::string> load_words(const char* filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n";
        std::exit(1);
    }

    std::vector<std::string> words;
    std::string w1, w2;
    while (in >> w1 >> w2) {
        words.push_back(w1 + " " + w2);
    }
    return words;
}

// -----------------------------------------------------------------------------
// generateTrace for LRU profile
// -----------------------------------------------------------------------------
void generateTrace(const unsigned seed,
                   const std::size_t N,
                   TraceConfig &config,
                   const std::vector<std::string>& words,
                   std::mt19937 &rng)
{
    // open output
    auto outputFileName = config.makeTraceFileName(seed, N);
    std::cout << "File name: " << outputFileName << std::endl;
    std::ofstream out(outputFileName.c_str());
    if (!out.is_open()) {
        std::cerr << "Failed to open file " << outputFileName << std::endl;
        exit(1);
    }

    out << config.profileName << " " << N << " " << seed << '\n';

    const std::size_t needed = 4 * N;

    if (words.size() < needed) {
        std::cerr << "File too small\n";
        std::exit(1);
    }

    // ---- pools ----
    std::vector<std::size_t> pool1;
    pool1.reserve(N);
    for (std::size_t i = 0; i < N; ++i)
        pool1.push_back(i);

    std::vector<std::size_t> pool2;
    pool2.reserve(5 * N);
    for (std::size_t i = N; i < 2*N; ++i)
        for (int k = 0; k < 5; ++k)
            pool2.push_back(i);

    std::vector<std::size_t> pool3;
    pool3.reserve(6 * N);
    for (std::size_t i = 2*N; i < 4*N; ++i)
        for (int k = 0; k < 3; ++k)
            pool3.push_back(i);

    // combine pools
    std::vector<std::size_t> bag;
    bag.reserve(12 * N);

    bag.insert(bag.end(), pool1.begin(), pool1.end());
    bag.insert(bag.end(), pool2.begin(), pool2.end());
    bag.insert(bag.end(), pool3.begin(), pool3.end());

    // shuffle
    std::shuffle(bag.begin(), bag.end(), rng);


    // ---- LRU Algorithm ----
    std::list<std::string> LRU_list; // front() = MRU, back() = LRU

    std::unordered_map<std::string, std::list<std::string>::iterator> resident_map;
    resident_map.reserve(N); // reserve for at most N words

    for (auto idx : bag) // for each index in bag
    {
        const std::string &w = words[idx];  // includes both tokens: "word1 word2"
        auto it = resident_map.find(w);

        if (it != resident_map.end())
        {
            // HIT
            // 1. Remove the node where w is currently stored
            LRU_list.erase(it->second);

            // 2. Insert w again at the most-recently-used position
            LRU_list.push_front(w);

            // 3. Update the iterator stored in the map
            it->second = LRU_list.begin();

            // 4. Emit the I w line
            out << "I " << w << "\n";
        }
        else if (resident_map.size() < N)
        {
            // MISS, space available
            LRU_list.push_front(w);
            resident_map[w] = LRU_list.begin();
            out << "I " << w << "\n";
        }
        else
        {
            // MISS, full -> evict LRU
            const std::string victim = LRU_list.back();
            out << "E " << victim << "\n";
            LRU_list.pop_back();
            resident_map.erase(victim);

            // insert new
            LRU_list.push_front(w);
            resident_map[w] = LRU_list.begin();
            out << "I " << w << "\n";
        }
    }
}


// -----------------------------------------------------------------------------
// main
// -----------------------------------------------------------------------------
int main() {

    TraceConfig config(std::string("lru_profile"));
    auto words = load_words(WORDS_FILE);

    for (auto seed : config.seeds) {
        std::mt19937 rng(seed);
        for (auto N : config.Ns) {
            generateTrace(seed, N, config, words, rng);
        }
    }

    return 0;
}