/**
 * Find DNA sequence using a random generator given sequences
 * and their % found.
 *
 * Write a pRNG class that can create reproducible random sequences.
 *
 * Given a probability of DNA sequences (pairs of 2), generate DNA
 * sequence with a specific seed (for random number generator).
 *
 * Reference: https://www.fluentcpp.com/2019/05/24/how-to-fill-a-cpp-collection-with-random-values/
 */
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <iostream>
#include <unordered_map>

class RandomDevice {
public:
    RandomDevice(unsigned long n)
        : rand_seed_(n), engine_(rand_seed_)
    {

    }

    int RandInt(int min, int max)
    {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(engine_);
    }

private:
    unsigned long rand_seed_;
    std::mt19937 engine_;
};

class RandomNumberBetween
{
public:
    RandomNumberBetween(int low, int high)
        : random_engine_{std::random_device{}()}
        , distribution_{low, high}
        {

        }

    int operator()()
    {
        return distribution_(random_engine_);
    }

private:
    // Mersenne Twister algorithm.
    std::mt19937 random_engine_;
    std::uniform_int_distribution<int> distribution_;
};

template <class T>
class DiscreteGenerator
{
public:
    DiscreteGenerator(unsigned long seed, std::vector<T> distribution)
        : rand_seed_(seed)
        , random_engine_(rand_seed_)
        , distribution_(distribution.begin(), distribution.end())
    {
    }

    T operator()()
    {
        return distribution_(random_engine_);
    }
private:
    unsigned long rand_seed_;
    std::mt19937 random_engine_;
    std::discrete_distribution<> distribution_;
};

std::vector<std::string> GenerateDNASeq(size_t len, size_t count, unsigned long seed)
{
    std::vector<std::string> res;
    std::vector<int> dist{20, 30, 30, 20};
    std::unordered_map<int, std::string> m;
    m[0] = "A";
    m[1] = "T";
    m[2] = "G";
    m[3] = "C";

    DiscreteGenerator<int> dg(seed, dist);
    for (size_t c = 0; c < count; c++) {
        std::string new_seq("");
        for (size_t i = 0; i < len; i++) {
            std::cout << dg();
            new_seq += m[dg()];
        }
        res.emplace_back(new_seq);
    }

    return res;
}

template <class T>
void PrintVect(const std::vector<T>& v)
{
    for (const auto& e : v)
        std::cout << e << std::endl;
    std::cout << std::endl;
}

int main()
{
    std::vector<std::string> tc = GenerateDNASeq(100, 4, 10);
    PrintVect(tc);
    return 0;
}
