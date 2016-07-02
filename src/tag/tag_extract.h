

#ifndef TAG_EXTRACT_H
#define TAG_EXTRACT_H


#include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<vector>

using namespace std;

class TagExtractor{
 public:
     TagExtractor(string tags_path, string stopword_path, string labels_path, string idf_path, string label_pair_path);
     ~TagExtractor();
 private:
     set<string> tags;
     set<string> stopword;
     set<string> labels;
     map<string, float> idf;
     set< pair<string, string> >label_pair;
};


#endif /* TAG_EXTRACT_H */

