//
// Created by Deuce Palmer on 1/23/22.
//

#include "Tweet.h"
Tweet::Tweet(){
}
Tweet::Tweet(DSString& id, DSString& sent, DSString& twet){
    ID = id;
    sentiment = sent;
    tweet = twet;
}
Tweet::Tweet(DSString& id, DSString& twet){
    ID = id;
    tweet = twet;
}
Tweet::~Tweet(){
    //needs nothing since all variables are DSStrings
}
Tweet& Tweet::operator= (const Tweet& entry){
    DSString identity = entry.ID;
    this->ID = identity;
    DSString sent = entry.sentiment;
    this->sentiment = sent;
    DSString twet = entry.tweet;
    this->tweet = twet;
    return *this;
}
void Tweet::setId(DSString& id){
    ID = id;
}
DSString Tweet::getId(){
    return ID;
}
void Tweet::setTweet(DSString& twet){
    tweet = twet;
}
DSString Tweet::getTweet(){
    return tweet;
}
void Tweet::setSent(DSString& sent){
    sentiment = sent;
}
DSString Tweet::getSent(){
    return sentiment;
}
void Tweet::parse(unordered_map<DSString, double>& dict){
    int z = tweet.numberOfWords();
    for (int x=0; x<z; x++){
        int w=0;
        auto it = dict.find(tweet.parse(x));//searches for word already seen
        if (it != dict.end()){
            w++;
            if (sentiment[0] == '4'){ //if this word is seen positively, add to the sentiment
                it->second += 2;
            }
            if (sentiment[0] == '0'){//if negative, subrtact
                it->second -= 2;
            }
        }
        if (w==0){//only runs if the parsed word has not been seen before
            if (sentiment[0]=='4') {//creates a new entry that is positive
                dict.insert(make_pair(tweet.parse(x), 2));
            }
            if (sentiment[0]=='0') {//creates a new entry that is negative
                dict.insert(make_pair(tweet.parse(x), -2));
            }
        }
    }
}
void Tweet::calcSent(unordered_map<DSString, double>& dict){
    char* pos = new char('4');
    char* neg = new char('0');
    DSString positive(pos);
    DSString negative(neg);
    int sent = 0;
    //where the real algorithm is, by adding up all the words sents with their sent values
    int z = tweet.numberOfWords();
    for (int x=0; x<z; x++){
        auto it = dict.find(tweet.parse(x));
        if (it != dict.end()){
            if (it->second > 10 || it->second < -10){
                sent += (it->second)*10;//give more significant words a larger effect on the end sentiment
            } else {
                sent += (it->second);//lesser signifacnt word do not have a mutliple
            }
        }
    }
    if (sent > 0){
        sentiment = positive;
    } else{
        sentiment = negative;
    }
}
