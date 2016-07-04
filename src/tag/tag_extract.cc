#include<algorithm>
#include "tag_extract.h"
#include "utils.h"

TagExtractor::TagExtractor(std::string tags_path, std::string stopword_path, std::string labels_path, std::string idf_path, std::string label_pair_path) {
    all_tags = utils::get_set(tags_path);
    stopword = utils::get_set(stopword_path);
    labels = utils::get_set(labels_path);
    label_pair = utils::get_map2(label_pair_path);
    idf = utils::get_map(idf_path);
}

TagExtractor::~TagExtractor() {
    all_tags.clear();
    stopword.clear();
    labels.clear();
    label_pair.clear();
    idf.clear();
}

bool cmp(std::pair<std::string, float> a, std::pair<std::string, float> b) {
    return a.second > b.second;
}

std::vector< std::pair<std::string, float> > TagExtractor::extract(std::vector<std::string> words) {
    std::map <std::string, int> word_freq;
    for(std::string s: words) {
        if(word_freq.find(s) != word_freq.end()) {
            word_freq[s] += 1;
        }else{
            word_freq.insert(std::make_pair(s, 1));
        }
    }

    std::vector< std::pair<std::string, float> > tfidf;
    for(std::map<std::string, int>::iterator pos = word_freq.begin(); pos != word_freq.end(); pos++) {
        float tf = 1.0 * pos->second / words.size();
        
        std::map<std::string, float>::iterator it = idf.find(pos->first);
        if(it != idf.end()) {
            tfidf.push_back(make_pair(it->first, tf * 1.0 * (it->second)));
        }
    }
    std::sort(tfidf.begin(), tfidf.end(), cmp);

    std::vector< std::pair<std::string, float> > cadidate_tags;
    for(unsigned int i = 0; i < 20; i++) {
        if(all_tags.find(tfidf[i].first) != all_tags.end())
            cadidate_tags.push_back(tfidf[i]);
    }

    std::vector<std::pair<std::string, float> > label_score;
    for(std::set<std::string>::iterator pos = labels.begin(); pos != labels.end(); pos++) {
        float socre = 0;
        float sum_tfidf = 0;
        for(unsigned int i = 0; i < cadidate_tags.size(); i++) {
            std::map< std::pair<std::string, std::string>,float >::iterator it = label_pair.find(make_pair(cadidate_tags[i].first， *pos));
            if(it != label_pair.end()) {
                socre += 1.0* it->second * cadidate_tags[i].second;
                sum_tfidf += cadidate_tags[i].second;
            }
        }
        if(socre > 0) 
            label_score.push_back(make_pair(*pos, socre/sum_tfidf));
    }

    std::sort(label_score.begin(), label_score.end(), cmp);

    std::vector<std::pair<std::string, float> >predict_result;
    if(label_score.size() > 0) {
        std::string predict_label = label_score[0].first;
        float predict_label_score = label_score[0].second;
        predict_result.push_back(std::make_pair(predict_label, predict_label_score));
    }
    int predict_size = cadidate_tags.size() > 5? 5: cadidate_tags.size();
    for(unsigned int i = 0; i <predict_size; i ++) {
        predict_result.push_back(cadidate_tags[i]);
    }
    return predict_result;
}
