/**
 * The Daily Byte
 *
 * Given a string s, remove all the vowels it contains and return the resulting
 * string.
 */

#include <string>
#include <cstdio>

using std::string;


void RemoveVowels(string& s)
{
    for (int i = 0; i < static_cast<int>(s.size()); i++) {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' ||
                s[i] == 'o' || s[i] == 'u')
            s.erase(i--);
    }
}

int main()
{
    string tc_s1("aeiou");
    string tc_s2("byte");
    string tc_s3("xyz");

    printf("%s\n", tc_s1.c_str());
    printf("%s\n", tc_s2.c_str());
    printf("%s\n", tc_s3.c_str());
    RemoveVowels(tc_s1);
    RemoveVowels(tc_s2);
    RemoveVowels(tc_s3);
    printf("%s\n", tc_s1.c_str());
    printf("%s\n", tc_s2.c_str());
    printf("%s\n", tc_s3.c_str());

    return 0;
}
