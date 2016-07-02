#include "tag_extract.h"
#include "utils.h"


TagExtractor::TagExtractor(string tags_path, string stopword_path, string labels_path, string idf_path, string label_pair_path) {
    tags = utils::get_set(tags_path);
    stopword = utils::get_set(stopword_path);
    labels = utils::get_set(labels_path);
    label_pair = utils::get_set2(labels_path);
    idf = utils::get_map(filename);
}

TagExtractor::~TagExtractor() {
    tags.clear();
    stopword.clear();
    labels.clear();
    label_pair.clear();
    idf.clear();
}
