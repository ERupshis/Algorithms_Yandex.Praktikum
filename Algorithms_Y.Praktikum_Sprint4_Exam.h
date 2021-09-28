#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string_view>
#include <algorithm>
#include <cassert>
#include <list>


namespace s4_exam_problems {
	using namespace std::literals;

	//SEND ID: 53581054

	// SearchServer is a class that keep all docs data in big dictionary where's unique words are keys. 
	// Value of these keys are another sub dictionaries where's keys are documents ID and values - count of 
	// word's mentions int the document.
	// This way of data storage helps to decrease request's preparation time due to we don't check all docs invidually, 
	// but only words check is needed
	// (SearchServer don't take into account docs that don't have any word in request)

	// Time Complexity:
	// AddDocument() - O(n), where n is a size (length) of document 
	//    - find and recognize word in document - O(n)
	//    - extract this word from document - O(n)
	//    - add word in database - O(1) on Average, O(N) - worst case in case of extending unordered_map. 
	//		N - is a number of words in the database at the moment of adding new word
	// SearchDocument() - (O(n + N * K + M * logM), where n - size (length) of request, 
	//												N - number of words in request, 
	//												K - number of docs which have exact word, 
	//												M - number of relevant docs
	//    - ParseRequest() - O(n), where n is a size (length) of request (This method is mostly similar to AddDocument() 
	//		except word adding in database
	//    - CountDocsRelevance() - O(N * K) where N - number of words in request, K - number of docs which have exact word. 
	//		K - is different for words.
	//    - ConvertDocsRelevanceMapIntoVector() - O(M * logM) where M is a number of relevant documents
	//       - convert data from map into vector for next sort -  O(M)
	//		 - sort vector of relevant docs - O(M * logM)
	//	  - GetResponceToRequest() - O(1) due to we consider only 5 most relevant docs in result
	// 
	//  Space Complexity: - Constant memory allocation - O(N * K), where N is number of unique words, 
	//						K - number of docs where exact words is mentioned. (K is different for words)
	//					  - Temporary memory allocation - O(M + 2 * L). (description see below)
	//	  - ParseRequest() - Temporary memory allocation - O(M), where M is a number of unique words in request
	//    - CountDocsRelevance() - Temporary memory allocation - O(L), where L is a number of relevant docs in database
	//    - ConvertDocsRelevanceMapIntoVector() - Temporary memory allocation - O(L), where L is a number of relevant docs in database
	//    - GetResponceToRequest() - Temporary memory allocation - O(1), size of request responce.


	class SearchServer {
	public:
		SearchServer() = default;

		void AddDocument(const std::string& str, int id) {			
			size_t pos = 0;
			while (true) {
				size_t space = str.find(' ', pos);
				if (space == std::string::npos) {
					++db_[str.substr(pos)][id];					
					break;
				}
				else {
					++db_[str.substr(pos, space - pos)][id];
					pos = space + 1;
				}
			}			
		}

		std::string SearchDocument(const std::string& str) {
			std::unordered_set<std::string> request = ParseRequest(str);	
			std::unordered_map<int, int> relevance_map = CountDocsRelevance(request);			
			std::vector<DocRelevance> sorted_relev_docs = ConvertDocsRelevanceMapIntoVector(relevance_map);
			return GetResponceToRequest(sorted_relev_docs);			
		}

	private:
		struct DocRelevance {
			int id = 0;
			int relevance_index = 0;

			bool operator < (const DocRelevance& other) {
				if (relevance_index == other.relevance_index) {
					return id < other.id;
				}
				return relevance_index > other.relevance_index;
			}
		};

		std::unordered_map<std::string, std::unordered_map<int, int>> db_;	

		///// SearchDocument() submethods
		std::unordered_set<std::string> ParseRequest(const std::string& str) {
			std::unordered_set<std::string> res;
			size_t pos = 0;
			while (true) {
				size_t space = str.find(' ', pos);
				if (space == std::string::npos) {
					res.insert(str.substr(pos));
					break;
				}
				else {
					res.insert(str.substr(pos, space - pos));
					pos = space + 1;
				}
			}
			return res;
		}

		std::unordered_map<int, int> CountDocsRelevance(const std::unordered_set<std::string>& request) {
			std::unordered_map<int, int> res;
			for (const std::string& word : request) {
				if (db_.count(word)) {
					for (const auto& elem : db_.at(word)) {
						res[elem.first] += elem.second;
					}
				}
			}
			return res;
		}

		std::vector<DocRelevance> ConvertDocsRelevanceMapIntoVector(const std::unordered_map<int, int>& relevance_map) {
			std::vector<DocRelevance> res;
			res.reserve(relevance_map.size());
			for (const auto& elem : relevance_map) {
				res.push_back({ elem.first, elem.second });
			}
			std::sort(res.begin(), res.end());
			return res;
		}
		
		std::string GetResponceToRequest(const std::vector<DocRelevance>& docs) {
			bool f = false;
			std::string res;
			for (size_t i = 0; i < 5 && i < docs.size(); ++i) {
				if (docs[i].relevance_index > 0) {
					if (f) {
						res.push_back(' ');
					}
					else {
						f = true;
					}
					res += std::to_string(docs[i].id);
				}
			}
			return res;
		}
	};

	void A_SearchServer(std::istream& input, std::ostream& output) {
		int n;
		input >> n;
		input.get(); // remove line break
		SearchServer server;

		for (int i = 0; i < n; ++i) {
			std::string doc;
			std::getline(input, doc);
			server.AddDocument(doc, i + 1);
		}

		int m;
		input >> m;
		input.get(); // remove line break

		for (int i = 0; i < m; ++i) {
			std::string doc;
			std::getline(input, doc);
			output << server.SearchDocument(doc) << '\n';
		}
	}

	/*-------------------------------------------------------------------------*/
	//SEND ID: 53622145

	// HashMap - associative array with chain method colission resolving.
	// database container consist of default vector with list as values inside. List's value - pair of an integer key and integer value
	// Max size of HashMap was choosen according problem task - a little bit higher odd number than maximum possible values in HashMap (100'003)
	// All three methods get access to the bucket of array by taking module from key. Main condition is executed - key range at least should be 
	// higher than size of array. Thank to it, values in HashMap will be split evenly in all array's buckets.
	// I suppose that Time complexity of Chain Method and Open Adressing Method is equal due to we have to check all value where hash of key points us
	// Time Complexity:
	//	- Put() - O(N) on Average where N is a number of elements in considering bucket at the current moment. Best Case - O(1) means that this new 
	//	{key, value} pair will be the first in designation bucket. If seeking key exists and is located somewhere in the middle of list in list than N will be less than bucket's size.
	//	- Get() - O(N) on Average where N is a number of elements in considering bucket at the current moment. Best Case - O(1) means that seeking pair
	//	is in head of bucket's list. If seeking key exists and is located somewhere in the middle of list than N will be less than bucket's size. 
	//	- Delete() - O(N) on Average where N is a number of elements in considering bucket at the current moment. Best Case - O(1) means that seeking pair
	//	is in head of bucket's list. If seeking key exists and is located somewhere in the middle of list than N will be less than bucket's size. 
	// Space Complexity:
	//  - Constant required space - O(N), where N is a number of unique pairs (all pairs have different keys). Size of array was choosen acording problem task
	//  In the task key may have unsigned int value up to 10^9. In case of evenly distribution of pairs through all buckets, every bucket will contain 
	//  10^4 pairs inside. Buckets quantity may be increased for current task. In this way time complexity of methods will be reduced.
	//	- Temporary required space - O(1) for all methods. 

	class HashMap {
	public:
		explicit HashMap(size_t size) {
			db_.resize(size);
		}

		void Put(int key, int value) {			
			std::list<Pair>& bucket = db_[key % db_.size()];
			for (auto it = bucket.begin(); it != bucket.end(); ++it) {
				if (key == it->key) {
					it->value = value;
					return;
				}
			}
			bucket.push_front({ key, value });
		}

		int Get(int key) const { // -1 means that element was not found
			const std::list<Pair>& bucket = db_[key % db_.size()];
			int res = -1;
			for (auto it = bucket.begin(); it != bucket.end(); ++it) {
				if (key == it->key) {
					res = it->value;	
					break;
				}
			}
			return res;
		}

		int Delete(int key) {
			int res = -1;
			std::list<Pair>& bucket = db_[key % db_.size()];			
			for (auto it = bucket.begin(); it != bucket.end(); ++it) {
				if (key == it->key) {
					res = it->value;
					bucket.erase(it);
					break;
				}
			}
			return res;
		}


	private:
		struct Pair {
			int key = -1;
			int value = -1;
		};

		std::vector<std::list<Pair>> db_;
	};

	void ResToOutStream(std::ostream& output, int res) {
		if (res == -1) {
			output << "None"s << '\n';
		}
		else {
			output << res << '\n';
		}
	}

	void B_HashTable(std::istream& input, std::ostream& output) {
		HashMap map(100'003);
		int n = 0;
		input >> n;
		
		for (int i = 0; i < n; ++i) {
			std::string req;
			input >> req;
			int key = -1, value = -1;
			if (req == "put"s) {
				input >> key >> value;
				map.Put(key, value);
			}
			else if (req == "get"s) {
				input >> key;
				ResToOutStream(output, map.Get(key));
			}
			else if (req == "delete"s) {
				input >> key;
				ResToOutStream(output, map.Delete(key));
			}
		}		
	}
}

namespace s4_exam_tests {
	using namespace std::literals;
	void A_SearchServer() {
		{
			std::stringstream input;
			input << "3"s << '\n'
				<< "i love coffee"s << '\n'
				<< "coffee with milk and sugar"s << '\n'
				<< "free tea for everyone"s << '\n'
				<< "3"s << '\n'
				<< "i like black coffee without milk"s << '\n'
				<< "everyone loves new year"s << '\n'
				<< "mary likes black coffee without milk"s;
			std::ostringstream output(std::ios_base::ate);
			s4_exam_problems::A_SearchServer(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "1 2"s << '\n'
				<< "3"s << '\n'
				<< "2 1"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "6"s << '\n'
				<< "buy flat in moscow"s << '\n'
				<< "rent flat in moscow"s << '\n'
				<< "sell flat in moscow"s << '\n'
				<< "want flat in moscow like crazy"s << '\n'
				<< "clean flat in moscow on weekends"s << '\n'
				<< "renovate flat in moscow"s << '\n'
				<< "1"s << '\n'
				<< "flat in moscow for crazy weekends"s;
			std::ostringstream output(std::ios_base::ate);
			s4_exam_problems::A_SearchServer(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "4 5 1 2 3"s << '\n';
			assert(output.str() == res.str());
		}
	}

	/*-------------------------------------------------------------------------*/
	void B_HashTable() {
		{
			std::stringstream input;
			input << "7"s << '\n'
				<< "put 1 10"s << '\n'
				<< "get 1"s << '\n'
				<< "put 1 20"s << '\n'
				<< "get 1"s << '\n'
				<< "get 2"s << '\n'
				<< "delete 1"s << '\n'
				<< "get 1"s;
			std::ostringstream output(std::ios_base::ate);
			s4_exam_problems::B_HashTable(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "10"s << '\n'
				<< "20"s << '\n'
				<< "None"s << '\n'
				<< "20"s << '\n'
				<< "None"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "10"s << '\n'
				<< "get 1"s << '\n'
				<< "put 1 10"s << '\n'
				<< "put 2 4"s << '\n'
				<< "get 1"s << '\n'
				<< "get 2"s << '\n'
				<< "delete 2"s << '\n'
				<< "get 2"s << '\n'
				<< "put 1 5"s << '\n'
				<< "get 1"s << '\n'
				<< "delete 2"s;
			std::ostringstream output(std::ios_base::ate);
			s4_exam_problems::B_HashTable(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "None"s << '\n'
				<< "10"s << '\n'
				<< "4"s << '\n'
				<< "4"s << '\n'
				<< "None"s << '\n'
				<< "5"s << '\n'
				<< "None"s << '\n';
			assert(output.str() == res.str());
		}
		{
			std::stringstream input;
			input << "8"s << '\n'
				<< "get 9"s << '\n'
				<< "delete 9"s << '\n'
				<< "put 9 1"s << '\n'
				<< "get 9"s << '\n'
				<< "put 9 2"s << '\n'
				<< "get 9"s << '\n'
				<< "put 9 3"s << '\n'				
				<< "get 9"s;
			std::ostringstream output(std::ios_base::ate);
			s4_exam_problems::B_HashTable(static_cast<std::iostream&>(input), output);
			std::stringstream res;
			res << "None"s << '\n'
				<< "None"s << '\n'
				<< "1"s << '\n'
				<< "2"s << '\n'
				<< "3"s << '\n';
			assert(output.str() == res.str());
		}

	}

}
