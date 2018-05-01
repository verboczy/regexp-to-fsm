#include <iostream>

#include "statemachine.h"
//#include "node.h"

using namespace std;


void test_inner_expression() {
    StateMachineBuilder smb;
    {
        std::string ex = "a(b(da)*)*";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "a";
        std::cout << s1 << " exptected: 1, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "ab";
        std::cout << s2 << " exptected: 1, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "abda";
        std::cout << s3 << " exptected: 1, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "abbbbbbbb";
        std::cout << s4 << " exptected: 1, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "abbbbbbbbda";
        std::cout << s5 << " exptected: 1, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "abdadadada";
        std::cout << s6 << " exptected: 1, actual: " << smb.check(s6) << std::endl;
        std::string s7 = "abbdadabda";
        std::cout << s7 << " exptected: 1, actual: " << smb.check(s7) << std::endl;

        std::string s8 = "bbdadabda";
        std::cout << s8 << " exptected: 0, actual: " << smb.check(s8) << std::endl;
        std::string s9 = "abdaa";
        std::cout << s9 << " exptected: 0, actual: " << smb.check(s9) << std::endl;
        std::string s10 = "abdd";
        std::cout << s10 << " exptected: 0, actual: " << smb.check(s10) << std::endl;
        std::string s11 = "ada";
        std::cout << s11 << " exptected: 0, actual: " << smb.check(s11) << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
    }
    {
        std::string ex = "a(b(d(c*e*)*a)*b)*f";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "af";
        std::cout << s1 << " exptected: 1, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "abbf";
        std::cout << s2 << " exptected: 1, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "abdceabf";
        std::cout << s3 << " exptected: 1, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "abbbbbdadadceabf";
        std::cout << s4 << " exptected: 1, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "abbbbbdadadabf";
        std::cout << s5 << " exptected: 1, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "abbbbbdadadeeeeeeeeeeeeeabf";
        std::cout << s6 << " exptected: 1, actual: " << smb.check(s6) << std::endl;
        std::string s7 = "abbbbbdadadcccccccccccccabf";
        std::cout << s7 << " exptected: 1, actual: " << smb.check(s7) << std::endl;
        std::string s8 = "abbbbbdadadceecceeececeabf";
        std::cout << s8 << " exptected: 1, actual: " << smb.check(s8) << std::endl;

        std::string s9 = "abdaaf";
        std::cout << s9 << " exptected: 0, actual: " << smb.check(s9) << std::endl;
        std::string s10 = "abf";
        std::cout << s10 << " exptected: 0, actual: " << smb.check(s10) << std::endl;
        std::string s11 = "abbbbbdadadcebf";
        std::cout << s11 << " exptected: 0, actual: " << smb.check(s11) << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
    }
}

void test_simple_inner_expression() {
    StateMachineBuilder smb;
    {
        std::string ex = "a(bd)*a";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "aa";
        std::cout << s1 << " exptected: 1, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "abda";
        std::cout << s2 << " exptected: 1, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "abdbdbdbdbda";
        std::cout << s3 << " exptected: 1, actual: " << smb.check(s3) << std::endl;

        std::string s4 = "abd";
        std::cout << s4 << " exptected: 0, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "aba";
        std::cout << s5 << " exptected: 0, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "ada";
        std::cout << s6 << " exptected: 0, actual: " << smb.check(s6) << std::endl;
        std::string s7 = "aabda";
        std::cout << s7 << " exptected: 0, actual: " << smb.check(s7) << std::endl;
        std::string s8 = "adba";
        std::cout << s8 << " exptected: 0, actual: " << smb.check(s8) << std::endl;
        std::string s9 = "a";
        std::cout << s9 << " exptected: 0, actual: " << smb.check(s9) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "a(bd)*a(de*f)*";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "aa";
        std::cout << s1 << " exptected: 1, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "abdadef";
        std::cout << s2 << " exptected: 1, actual: " << smb.check(s2) << std::endl;
        std::string s211 = "abdadf";
        std::cout << s211 << " exptected: 1, actual: " << smb.check(s211) << std::endl;
        std::string s3 = "abdbdbdbdbdadeeeeeeeeeeeeeeeeeeeeeeeeeeefdefdeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef";
        std::cout << s3 << " exptected: 1, actual: " << smb.check(s3) << std::endl;
        std::string s311 = "abda";
        std::cout << s311 << " exptected: 1, actual: " << smb.check(s311) << std::endl;
        std::string s411 = "aadefdefdeeef";
        std::cout << s411 << " exptected: 1, actual: " << smb.check(s411) << std::endl;

        std::string s4 = "a";
        std::cout << s4 << " exptected: 0, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "abdaa";
        std::cout << s5 << " exptected: 0, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "abdad";
        std::cout << s6 << " exptected: 0, actual: " << smb.check(s6) << std::endl;
        std::string s7 = "abddef";
        std::cout << s7 << " exptected: 0, actual: " << smb.check(s7) << std::endl;
        std::string s8 = "adbaa";
        std::cout << s8 << " exptected: 0, actual: " << smb.check(s8) << std::endl;
        std::string s9 = "aae";
        std::cout << s9 << " exptected: 0, actual: " << smb.check(s9) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "(ab)*(cd)*(ef)*(gh)*";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 1, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "ab";
        std::cout << s2 << " exptected: 1, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "abcd";
        std::cout << s3 << " exptected: 1, actual: " << smb.check(s3) << std::endl;
        std::string s31 = "abcdef";
        std::cout << s31 << " exptected: 1, actual: " << smb.check(s31) << std::endl;
        std::string t1 = "abcdefgh";
        std::cout << t1 << " exptected: 1, actual: " << smb.check(t1) << std::endl;
        std::string t2 = "cd";
        std::cout << t2 << " exptected: 1, actual: " << smb.check(t2) << std::endl;
        std::string t3 = "cdef";
        std::cout << t3 << " exptected: 1, actual: " << smb.check(t3) << std::endl;
        std::string t4 = "cdefgh";
        std::cout << t4 << " exptected: 1, actual: " << smb.check(t4) << std::endl;
        std::string t5 = "ef";
        std::cout << t5 << " exptected: 1, actual: " << smb.check(t5) << std::endl;
        std::string t6 = "efgh";
        std::cout << t6 << " exptected: 1, actual: " << smb.check(t6) << std::endl;
        std::string t7 = "gh";
        std::cout << t7 << " exptected: 1, actual: " << smb.check(t7) << std::endl;
        std::string t8 = "ababababababcdcdcdcdcdcdcdcdefefefefefefefefefefefefefghghghghghghghghgh";
        std::cout << t8 << " exptected: 1, actual: " << smb.check(t8) << std::endl;
        std::string t9 = "abef";
        std::cout << t9 << " exptected: 1, actual: " << smb.check(t9) << std::endl;
        std::string t10 = "abgh";
        std::cout << t10 << " exptected: 1, actual: " << smb.check(t10) << std::endl;
        std::string t11 = "cdgh";
        std::cout << t11 << " exptected: 1, actual: " << smb.check(t11) << std::endl;

        std::string s4 = "cdab";
        std::cout << s4 << " exptected: 0, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "aab";
        std::cout << s5 << " exptected: 0, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "abhg";
        std::cout << s6 << " exptected: 0, actual: " << smb.check(s6) << std::endl;
        std::string s7 = "ghef";
        std::cout << s7 << " exptected: 0, actual: " << smb.check(s7) << std::endl;
        std::string s8 = "ababababababcdcdcdcdcdcdcdefefefefefefefghghghghghghghh";
        std::cout << s8 << " exptected: 0, actual: " << smb.check(s8) << std::endl;
        std::string s9 = "a";
        std::cout << s9 << " exptected: 0, actual: " << smb.check(s9) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
}


void test_no_inner() {
    StateMachineBuilder smb;
    {
        std::string ex = "a*";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 1, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 1, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        std::cout << s3 << " exptected: 1, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "aaaaaaaaaaaaaan";
        std::cout << s4 << " exptected: 0, actual: " << smb.check(s4) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "a";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 0, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 1, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        std::cout << s3 << " exptected: 0, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "aaaaaaaaaaaaaan";
        std::cout << s4 << " exptected: 0, actual: " << smb.check(s4) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "ab";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 0, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 0, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "ab";
        std::cout << s3 << " exptected: 1, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "aba";
        std::cout << s4 << " exptected: 0, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "abb";
        std::cout << s5 << " exptected: 0, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "ba";
        std::cout << s6 << " exptected: 0, actual: " << smb.check(s6) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "ab*";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 0, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 1, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "ab";
        std::cout << s3 << " exptected: 1, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "aba";
        std::cout << s4 << " exptected: 0, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "abb";
        std::cout << s5 << " exptected: 1, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "ba";
        std::cout << s6 << " exptected: 0, actual: " << smb.check(s6) << std::endl;
        std::string s7 = "abba";
        std::cout << s7 << " exptected: 0, actual: " << smb.check(s7) << std::endl;
        std::string s8 = "abbbbbbbbbbbbbbbbbbbbbbb";
        std::cout << s8 << " exptected: 1, actual: " << smb.check(s8) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "a*b";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 0, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 0, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "ab";
        std::cout << s3 << " exptected: 1, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "aba";
        std::cout << s4 << " exptected: 0, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "abb";
        std::cout << s5 << " exptected: 0, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "ba";
        std::cout << s6 << " exptected: 0, actual: " << smb.check(s6) << std::endl;
        std::string s7 = "abba";
        std::cout << s7 << " exptected: 0, actual: " << smb.check(s7) << std::endl;
        std::string s8 = "abbbbbbbbbbbbbbbbbbbbbbb";
        std::cout << s8 << " exptected: 0, actual: " << smb.check(s8) << std::endl;
        std::string s9 = "b";
        std::cout << s9 << " exptected: 1, actual: " << smb.check(s9) << std::endl;
        std::string s10 = "bb";
        std::cout << s10 << " exptected: 0, actual: " << smb.check(s10) << std::endl;
        std::string s11 = "aaaaaaaaaaaaaaaaaaaaaaaaab";
        std::cout << s11 << " exptected: 1, actual: " << smb.check(s11) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "a*b*";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 1, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 1, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "ab";
        std::cout << s3 << " exptected: 1, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "aba";
        std::cout << s4 << " exptected: 0, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "abb";
        std::cout << s5 << " exptected: 1, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "ba";
        std::cout << s6 << " exptected: 0, actual: " << smb.check(s6) << std::endl;
        std::string s7 = "abba";
        std::cout << s7 << " exptected: 0, actual: " << smb.check(s7) << std::endl;
        std::string s8 = "abbbbbbbbbbbbbbbbbbbbbbb";
        std::cout << s8 << " exptected: 1, actual: " << smb.check(s8) << std::endl;
        std::string s9 = "b";
        std::cout << s9 << " exptected: 1, actual: " << smb.check(s9) << std::endl;
        std::string s10 = "bb";
        std::cout << s10 << " exptected: 1, actual: " << smb.check(s10) << std::endl;
        std::string s11 = "aaaaaaaaaaaaaaaaaaaaaaaaab";
        std::cout << s11 << " exptected: 1, actual: " << smb.check(s11) << std::endl;
        std::cout << "-------------------------------------" << std::endl;

    }
    {
        std::string ex = "a*b*c";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 0, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 0, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "ab";
        std::cout << s3 << " exptected: 0, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "abc";
        std::cout << s4 << " exptected: 1, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "abb";
        std::cout << s5 << " exptected: 0, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "ba";
        std::cout << s6 << " exptected: 0, actual: " << smb.check(s6) << std::endl;
        std::string s7 = "abba";
        std::cout << s7 << " exptected: 0, actual: " << smb.check(s7) << std::endl;
        std::string s8 = "abbbbbbbbbbbbbbbbbbbbbbb";
        std::cout << s8 << " exptected: 0, actual: " << smb.check(s8) << std::endl;
        std::string s9 = "b";
        std::cout << s9 << " exptected: 0, actual: " << smb.check(s9) << std::endl;
        std::string s10 = "bb";
        std::cout << s10 << " exptected: 0, actual: " << smb.check(s10) << std::endl;
        std::string s11 = "aaaaaaaaaaaaaaaaaaaaaaaaab";
        std::cout << s11 << " exptected: 0, actual: " << smb.check(s11) << std::endl;
        std::string s12 = "aaaaaaaaaaaaaaaaaaaaaaaaabcccccccccccccccccccc";
        std::cout << s12 << " exptected: 0, actual: " << smb.check(s12) << std::endl;
        std::string s13 = "c";
        std::cout << s13 << " exptected: 1, actual: " << smb.check(s13) << std::endl;
        std::string s14 = "cb";
        std::cout << s14 << " exptected: 0, actual: " << smb.check(s14) << std::endl;
        std::string s15 = "bc";
        std::cout << s15 << " exptected: 1, actual: " << smb.check(s15) << std::endl;
        std::string s16 = "ac";
        std::cout << s16 << " exptected: 1, actual: " << smb.check(s16) << std::endl;
        std::string s17 = "aaaaaaaaaaaaaaaaaaaaaaaaabc";
        std::cout << s17 << " exptected: 1, actual: " << smb.check(s17) << std::endl;
        std::cout << "-------------------------------------" << std::endl;

    }
    {
        std::string ex = "a*b*c*";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 1, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 1, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "ab";
        std::cout << s3 << " exptected: 1, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "aba";
        std::cout << s4 << " exptected: 0, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "abb";
        std::cout << s5 << " exptected: 1, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "ba";
        std::cout << s6 << " exptected: 0, actual: " << smb.check(s6) << std::endl;
        std::string s7 = "abba";
        std::cout << s7 << " exptected: 0, actual: " << smb.check(s7) << std::endl;
        std::string s8 = "abbbbbbbbbbbbbbbbbbbbbbb";
        std::cout << s8 << " exptected: 1, actual: " << smb.check(s8) << std::endl;
        std::string s9 = "b";
        std::cout << s9 << " exptected: 1, actual: " << smb.check(s9) << std::endl;
        std::string s10 = "bb";
        std::cout << s10 << " exptected: 1, actual: " << smb.check(s10) << std::endl;
        std::string s11 = "aaaaaaaaaaaaaaaaaaaaaaaaab";
        std::cout << s11 << " exptected: 1, actual: " << smb.check(s11) << std::endl;
        std::string s12 = "aaaaaaaaaaaaaaaaaaaaaaaaabcccccccccccccccccccc";
        std::cout << s12 << " exptected: 1, actual: " << smb.check(s12) << std::endl;
        std::string s13 = "c";
        std::cout << s13 << " exptected: 1, actual: " << smb.check(s13) << std::endl;
        std::string s14 = "cb";
        std::cout << s14 << " exptected: 0, actual: " << smb.check(s14) << std::endl;
        std::string s15 = "bc";
        std::cout << s15 << " exptected: 1, actual: " << smb.check(s15) << std::endl;
        std::string s16 = "ac";
        std::cout << s16 << " exptected: 1, actual: " << smb.check(s16) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
}

void test_or_expressions() {
    StateMachineBuilder smb;
    {
        std::string ex = "a|b";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 0, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 1, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "b";
        std::cout << s3 << " exptected: 1, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "ab";
        std::cout << s4 << " exptected: 0, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "abb";
        std::cout << s5 << " exptected: 0, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "ba";
        std::cout << s6 << " exptected: 0, actual: " << smb.check(s6) << std::endl;
        std::string s7 = "abba";
        std::cout << s7 << " exptected: 0, actual: " << smb.check(s7) << std::endl;
        std::string s8 = "abbbbbbbbbbbbbbbbbbbbbbb";
        std::cout << s8 << " exptected: 0, actual: " << smb.check(s8) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "a|b|c|d";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 0, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 1, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "b";
        std::cout << s3 << " exptected: 1, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "ab";
        std::cout << s4 << " exptected: 0, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "abb";
        std::cout << s5 << " exptected: 0, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "ba";
        std::cout << s6 << " exptected: 0, actual: " << smb.check(s6) << std::endl;
        std::string s7 = "abba";
        std::cout << s7 << " exptected: 0, actual: " << smb.check(s7) << std::endl;
        std::string s8 = "abbbbbbbbbbbbbbbbbbbbbbb";
        std::cout << s8 << " exptected: 0, actual: " << smb.check(s8) << std::endl;
        std::string s9 = "c";
        std::cout << s9 << " exptected: 1, actual: " << smb.check(s9) << std::endl;
        std::string s10 = "d";
        std::cout << s10 << " exptected: 1, actual: " << smb.check(s10) << std::endl;
        std::string s11 = "ad";
        std::cout << s11 << " exptected: 0, actual: " << smb.check(s11) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "(a*b)*|(cd*ef)";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 1, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "b";
        std::cout << s2 << " exptected: 1, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "bbbb";
        std::cout << s3 << " exptected: 1, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "abaaaab";
        std::cout << s4 << " exptected: 1, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "cdef";
        std::cout << s5 << " exptected: 1, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "cef";
        std::cout << s6 << " exptected: 1, actual: " << smb.check(s6) << std::endl;
        std::string s7 = "cddddddddef";
        std::cout << s7 << " exptected: 1, actual: " << smb.check(s7) << std::endl;
        std::string s8 = "abcdef";
        std::cout << s8 << " exptected: 0, actual: " << smb.check(s8) << std::endl;
        std::string s9 = "bcef";
        std::cout << s9 << " exptected: 0, actual: " << smb.check(s9) << std::endl;
        std::string s10 = "cdefab";
        std::cout << s10 << " exptected: 0, actual: " << smb.check(s10) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
}

void test_plus_expressions() {
    StateMachineBuilder smb;
    {
        std::string ex = "a+";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 0, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 1, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "b";
        std::cout << s3 << " exptected: 0, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "aa";
        std::cout << s4 << " exptected: 1, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "aaaaaaaaaaaaaaaaaaaaaaaaaaa";
        std::cout << s5 << " exptected: 1, actual: " << smb.check(s5) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
    {
        std::string ex = "(a+b)+";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 0, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 0, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "ab";
        std::cout << s3 << " exptected: 1, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "aaaaab";
        std::cout << s4 << " exptected: 1, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "abb";
        std::cout << s5 << " exptected: 0, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "abababaaaaaaaaaaaaaab";
        std::cout << s6 << " exptected: 1, actual: " << smb.check(s6) << std::endl;
        std::string s7 = "abba";
        std::cout << s7 << " exptected: 0, actual: " << smb.check(s7) << std::endl;
        std::string s8 = "b";
        std::cout << s8 << " exptected: 0, actual: " << smb.check(s8) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
}

void test_everything() {
    StateMachineBuilder smb;
    {
        std::string ex = "ab(e(gh)*f)|i+c";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "abc";
        std::cout << s1 << " exptected: 0, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "abic";
        std::cout << s2 << " exptected: 1, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "abiiiic";
        std::cout << s3 << " exptected: 1, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "abefc";
        std::cout << s4 << " exptected: 1, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "abeghghghghfc";
        std::cout << s5 << " exptected: 1, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "abeghghghghfic";
        std::cout << s6 << " exptected: 0, actual: " << smb.check(s6) << std::endl;
        std::string s7 = "abfc";
        std::cout << s7 << " exptected: 0, actual: " << smb.check(s7) << std::endl;
    }
    {
        std::string ex = "(a(((b)))*)|(def*)+";
        smb.buildStateMachine(ex);
        std::cout << "State machine: " << ex << std::endl;
        std::string s1 = "";
        std::cout << s1 << " exptected: 0, actual: " << smb.check(s1) << std::endl;
        std::string s2 = "a";
        std::cout << s2 << " exptected: 1, actual: " << smb.check(s2) << std::endl;
        std::string s3 = "b";
        std::cout << s3 << " exptected: 0, actual: " << smb.check(s3) << std::endl;
        std::string s4 = "ab";
        std::cout << s4 << " exptected: 1, actual: " << smb.check(s4) << std::endl;
        std::string s5 = "abb";
        std::cout << s5 << " exptected: 1, actual: " << smb.check(s5) << std::endl;
        std::string s6 = "de";
        std::cout << s6 << " exptected: 1, actual: " << smb.check(s6) << std::endl;
        std::string s7 = "dededede";
        std::cout << s7 << " exptected: 1, actual: " << smb.check(s7) << std::endl;
        std::string s8 = "dedeffffffdef";
        std::cout << s8 << " exptected: 1, actual: " << smb.check(s8) << std::endl;
        std::string s9 = "abdef";
        std::cout << s9 << " exptected: 0, actual: " << smb.check(s9) << std::endl;
        std::string s10 = "df";
        std::cout << s10 << " exptected: 0, actual: " << smb.check(s10) << std::endl;
        std::string s11 = "ef";
        std::cout << s11 << " exptected: 0, actual: " << smb.check(s11) << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    }
}


int main()
{


    test_inner_expression();
    test_simple_inner_expression();
    test_no_inner();
    test_or_expressions();
    test_plus_expressions();
    test_everything();

    /*
    std::string user_input;
    std::cin >> user_input;

    while (user_input != "exit") {

        bool result = smb.check(user_input);
        std::cout << user_input << " is " << result << std::endl;

        std::cin >> user_input;
    }
    */
    return 0;
}
