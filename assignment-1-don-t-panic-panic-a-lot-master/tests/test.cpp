#include "../src/shell.h"
#include "../src/parser.h"
#include "../src/composite.h"

#include "gtest/gtest.h"
#include "../src/shell.h"
#include "../src/parser.h"
#include "../src/composite.h"

TEST(Composite, AddLeaf)
{
    Parser* parsed = new Parser();
    parsed->setString("asd#asd");
    parsed->parser();
    Composite* comp = new Composite();
    comp->add(parsed);
    EXPECT_EQ(comp->at(0), parsed->at(0));
}

TEST(Composite, FindAnd)
{
    Parser* parsed = new Parser();
    parsed->setString("a && b;");
    parsed->parser();
    Composite* comp = new Composite();
    comp->add(parsed);
    EXPECT_EQ("&&", comp->at(1)); 
}

TEST(Composite, FindOr)
{
    Parser* parsed = new Parser();
    parsed->setString("c || d");
    parsed->parser();
    Composite* comp = new Composite();
    comp->add(parsed);
    EXPECT_EQ("||", comp->at(1));
}

TEST(Composite, FindComment)
{
    Parser* parsed = new Parser();
    parsed->setString("e#f");
    parsed->parser();
    Composite* comp = new Composite();
    comp->add(parsed);
    EXPECT_EQ("#", comp->at(1));
}

TEST(Composite, getSize)
{
    Parser* parsed = new Parser();
    Parser* parsed1 = new Parser();
    parsed->setString("asd");
    parsed1->setString("dsa");
    Composite* comp = new Composite();
    comp->add(parsed);
    comp->add(parsed1);
    EXPECT_EQ(2, comp->size());
}

TEST(parserTest, semiColonParse)
{
    Parser* firstParse = new Parser();
    firstParse->setString("ls -a; echo hello && mkdir test || echo world; git status; exit");
    firstParse->parser();
        
    testing::internal::CaptureStdout();
    firstParse->print();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("PARSED VECTOR: ls -a ; echo hello && mkdir test || echo world ; git status ; exit ", output);
}

TEST(parserTest, ampParse)
{
    Parser* firstParse = new Parser();
    firstParse->setString("ls -a && echo hello && mkdir test && echo world && git status");
    firstParse->parser();

    testing::internal::CaptureStdout();
    firstParse->print();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("PARSED VECTOR: ls -a && echo hello && mkdir test && echo world && git status ", output);
}

TEST(parserTest, orParse)
{
    Parser* firstParse = new Parser();
    firstParse->setString("ls -a || echo hello || mkdir test || echo world || git status");
    firstParse->parser();

    testing::internal::CaptureStdout();
    firstParse->print();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("PARSED VECTOR: ls -a || echo hello || mkdir test || echo world || git status ", output);
}

TEST(parserTest, commendParse)
{
    Parser* firstParse = new Parser();
    firstParse->setString("ls -a # echo hello # mkdir test # echo world # git status");
    firstParse->parser();

    testing::internal::CaptureStdout();
    firstParse->print();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("PARSED VECTOR: ls -a # echo hello # mkdir test # echo world # git status ", output);
}   

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
