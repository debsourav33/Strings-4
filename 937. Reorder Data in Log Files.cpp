/*
Time: O(n)
Space: O(1)

Step 1: Bring all letter logs in front and all digit-logs at the bottom (preserving their orders)
Step 2: Sort first part of the logs array where the elements are letter-logs
*/

class Solution {
public:
    //checks if the content is digits (any character will be a digit)
    bool is_digit(string &s){
        return s[0] >= '0' && s[0] <= '9';
    }


    //decompose a log into id and content
    pair<string,string> parse(string &s){
        string id = "";
        string content = "";
        bool id_done = false;

        for(auto &c: s){
            if(id_done)  content += c;
            else if(c == ' ')  id_done = true;
            else  id += c;
        }

        return {id, content};
    }

    vector<string> reorderLogFiles(vector<string>& logs) {
        int swap_idx = logs.size()-1;
        int letter_cnt = 0;

        //swap all digits to end (preserving their orders) and all letters to begining
        for(int i=logs.size()-1; i>=0; i--){
            string &s = logs[i];
            auto p = parse(s);
            auto id = p.first, content = p.second;

            if(is_digit(content)){
                swap(logs[i], logs[swap_idx]); //swap_idx is farthest letter_log (or = i if no letter_log encountered)
                swap_idx--;
            }
            else{
                letter_cnt++; //increment letter_log cnt
            }
        }

        //for(auto s: logs)  cout<<s<<endl;

        //now all the letter-logs are at the beginning (from 0 to letter_cnt-1)
        //sort letter logs using custom comparator
        //[&] to capture the parse function by reference
        sort(logs.begin(), logs.begin()+letter_cnt, [&](string& s1, string& s2){
            auto p1 = parse(s1);
            auto p2 = parse(s2);

            if(p1.second == p2.second)  return p1.first < p2.first; //if contents same, sort by ids
            return p1.second < p2.second; //else, sort by content
        });

        return logs;
    }
};
