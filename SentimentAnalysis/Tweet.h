//
// Created by Deuce Palmer on 1/23/22.
//

#ifndef PA01_SENTIMENT_TWEET_H
#define PA01_SENTIMENT_TWEET_H
#include "DSString.h"
#include <vector>
#include <unordered_map>

using namespace std;

class Tweet {
private:
    DSString ID;
    DSString sentiment;
    DSString tweet;
public:
    /**
     * constructors and destructor
     */
    Tweet();
    Tweet(DSString& id, DSString& sent, DSString& twet); // for train data
    Tweet(DSString& id, DSString& twet);//for test data
    ~Tweet();
    /**
     * Overloaded Assignment Operator
     */
    Tweet& operator= (const Tweet&);
    /**
     * sets and gets of Tweets private data
     */
    void setId(DSString& id);
    DSString getId();
    void setTweet(DSString& twet);
    DSString getTweet();
    void setSent(DSString& sent);
    DSString getSent();
    /**
     * calculates the sentiment of all individual words
     * @param dict
     */
    void parse(unordered_map<DSString, double>& dict);
    /**
     * calculates final sentiment of an entire tweet
     * @param dict
     */
    void calcSent(unordered_map<DSString, double>& dict);
};
//added by Professor Fontenot so that unordered_map can work with a DSString
namespace std {
    template<>
    class hash<DSString> {
    public:
        size_t operator()(const DSString &arg) const {
            size_t h = 5381;
            int c;
            int len = arg.getLength();
            for (int i = 0; i<len; i++)
                h = ((h << 5) + h) + arg[i];
            return h;
        }
    };
}

#endif //PA01_SENTIMENT_TWEET_H
