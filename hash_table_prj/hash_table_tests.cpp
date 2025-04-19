 #include "hash_table.hpp"
 #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
 #include "doctest.h"
 #include <string>
  
 TEST_CASE("HashTable - Basic Operations") {
     HashTable<int, std::string> ht(10);
 
     SUBCASE("Insert and contains") {
         ht.insert(1, "one");
         CHECK(ht.contains(1) == true);
         CHECK(ht.contains(2) == false);
     }
 
     SUBCASE("Subscript operator") {
         ht[1] = "one";
         CHECK(ht[1] == "one");
         ht[1] = "new_one";
         CHECK(ht[1] == "new_one");
     }
 }
 
 TEST_CASE("HashTable - Iterator Functionality") {
     HashTable<int, std::string> ht(5);
     ht.insert(1, "one");
     ht.insert(2, "two");
     ht.insert(3, "three");
 
     SUBCASE("Range-based for loop") {
         std::set<int> keys;
         for (const auto& kv : ht) {
             keys.insert(kv.first);  // Используем . вместо ->
         }
         CHECK(keys.size() == 3);
         CHECK(keys.count(1) == 1);
         CHECK(keys.count(2) == 1);
         CHECK(keys.count(3) == 1);
     }
 
     SUBCASE("Begin and end") {
         auto it = ht.begin();
         CHECK((*it).first == 1);  // Используем * и . вместо ->
         CHECK((*it).second == "one");
         
         ++it;
         CHECK((*it).first == 2);
         CHECK((*it).second == "two");
     }
 }
 
 TEST_CASE("HashTable - Edge Cases") {
     SUBCASE("Empty table") {
         HashTable<int, std::string> ht(5);
         CHECK(!(ht.begin() != ht.end()));
         
         ht.insert(1, "one");
         CHECK(ht.begin() != ht.end());
     }
 
     SUBCASE("Collision handling") {
         HashTable<int, int> small_ht(1);  // Все элементы в одной корзине
         small_ht.insert(1, 10);
         small_ht.insert(2, 20);
         
         int sum = 0;
         for (const auto& kv : small_ht) {
             sum += kv.second;  // Используем . вместо ->
         }
         CHECK(sum == 30);
     }
 }