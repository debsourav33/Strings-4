/*
Time: O(n)
Space: O(1)

Handle positive and negative cases gracefully, with consideration of overflow
remember the negative max (INT_MIN) has a value 1 greater than positive max (INT_MAX)
Go through the comments to understand each step
*/

class Solution {
public:
    void ltrim(string &s){
        int n = s.length();
        int i;
        for(i=0;i<n;i++)  if(s[i]!=' ')  break;

        s = s.substr(i,s.length()-i);
    }

    int myAtoi(string s) {
        ltrim(s);

        int n = s.length();
        int maxi = 214748364; //7 or -8
        int div = 1e9;

        int val = 0;
        bool neg = s[0] == '-';

        int start = 0;
        if(s[0] == '+' || s[0] == '-')  start = 1;

        for(int i=start;i<n;i++){
            if(s[i] < '0' || s[i] > '9')  break;
            int curr = s[i] - '0';

            //if adding more digit makes overflow
            if(val > maxi || val/div > 0){ //val/div > 0 means val has 10 digits already (which is max)
                return neg ? INT_MIN : INT_MAX;
            }

            //if we can add only one more digit, add it such that overflow doesn't happen
            if(!neg and val == maxi){
                curr = min(7, curr);
                val = val* 10 + curr;
                continue;
            }

            //same for negative number
            if(neg and val == maxi){
                curr = min(8, curr);
                val *= -1;
                val = val * 10 - curr;
                

                //special case for negative
                if(i<s.length()-1 && s[i] >= '0' && s[i] <= '9')  return INT_MIN;
                else  return val;
            }

            //otherwise just add the new digit
            val = val* 10 + curr;
        }

        //return depending on the sign
        return neg ? -val : val;
    }
};
