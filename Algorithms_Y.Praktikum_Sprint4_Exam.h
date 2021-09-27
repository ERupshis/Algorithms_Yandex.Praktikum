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
	//SEND ID: ???

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

}
