/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include"utils.h"


std::set<std::string>  utils::get_set(std::string filename) {
    std::set<std::string> word;
    std::ifstream ifile;
    ifile.open(filename);
    while(ifile.good()) {
        std::string line;
        getline(ifile, line);
        word.insert(line);
    }
    return word;
}

std::set< std::pair<std::string, std::string> >  utils::get_set2(std::string filename) {
    std::set< std::pair<std::string, std::string> > word_pair;
    std::ifstream ifile;
    ifile.open(filename);
    while(ifile.good()) {
        std::string line;
        getline(ifile, line);
        std::vector<std::string> items = split(line, "\t");
        word_pair.insert(make_pair(items[0], items[1]));
    }
    return word_pair;
}

std::map<std::string,int> utils::get_map(std::string filename) {
    std::map<std::string,int> word_map;
    std::ifstream ifile;
    ifile.open(filename);
    while(ifile.good()) {
        std::string line;
        getline(ifile, line);
        std::vector<std::string> items = split(line, "\t");
        word_map.insert(std::pair<items[0], items[1]>);
    }
    return word_map;
}

std::vector<std::string> utils::split(const std::string &s, const std::string & seperator) {
    std::vector<std::string> v;
    std::string::size_type pos1, pos2;
    pos2 = s.find(seperator);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + seperator.size();
        pos2 = s.find(seperator, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
    return v;
}

void utils::libsvmFomatParse(char * line,feature_items & x, int &y) {
    char * label, * idx, * val, * endptr;
    label = strtok(line, " \t\n");
    int idx_int;
    int val_int;
    if(label == NULL)
        return;
    y = int(strtol(label, &endptr,10));
    if(endptr == label || *endptr != '\0')
        return;
    
    while(1) {
        idx = strtok(NULL, ":");
        val = strtok(NULL, " \t");
        if(val == NULL)
            break;
        idx_int = (int) strtol(idx, &endptr, 10);
        val_int = (int) strtol(val, &endptr, 10);
        x[idx_int] = val_int;
    }
}
