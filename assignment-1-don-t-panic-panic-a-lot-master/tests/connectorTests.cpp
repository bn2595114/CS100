
#include <vector>
#include "../src/shell.h"
#include "../src/semi.h"
#include "../src/end.h"
#include "../src/parentheses.h"
#include "../src/and.h"
#include "../src/or.h"

#include "gtest/gtest.h"

TEST(Semi, get)
{
    string x = "echo hello;";
    Semi* tree = new Semi(new Command(x));

    EXPECT_EQ(tree->getStr(),"s");
}

TEST(Semi, test_fail)
{
    Semi* s = new Semi(new Command("ec"));
    s->setFail(-1);

    EXPECT_EQ(s->getFail(),-1);
}

TEST(Semi, Semi)
{
    Semi* s = new Semi(new Command("a"));

    EXPECT_EQ(s->getFail(),0);

}

TEST(And, get)
{
    string x = "echo hello && echo hi";
    string y = "echo a";

    And* tree = new And(new Command(x), new Command(y));

    EXPECT_EQ(tree->getStr(),"a");
}

TEST(And, test_fail)
{
    And* a = new And(new Command("a"), new Command("b"));
    a->setFail(-1);

    EXPECT_EQ(a->getFail(), -1);

}

TEST(And, And)
{
    And* a = new And(new Command("a"), new Command("b"));

    EXPECT_EQ(a->getFail(), 0);
}

TEST(Or, get)
{
    string x = "echo a";
    string y = "echo b";

    Or* tree = new Or(new Command(x), new Command(y));

    EXPECT_EQ(tree->getStr(),"o");
}

TEST(Or, test_fail)
{
    Or* o = new Or(new Command("a"), new Command("b"));
    o->setFail(-1);

    EXPECT_EQ(o->getFail(),-1);

}

TEST(Or, Or)
{
    Or* o = new Or(new Command("a"), new Command("b"));

    EXPECT_EQ(o->getFail(),0);
}

TEST(End, get)
{
    string x = "echo a";
    
    End* tree = new End(new Command(x));

    EXPECT_EQ(tree->getStr(), "e");
  
}

TEST(End, test_fail)
{
    End* e = new End(new Command("a"));

    e->setFail(-1);

    EXPECT_EQ(e->getFail(), -1);
}

TEST(End, End)
{
    End* e = new End(new Command("a"));

    EXPECT_EQ(e->getFail(), 0);
}

TEST(Parentheses, test_fail)
{
    vector<string> str;
    Parentheses* p = new Parentheses(str);
    p->setFail(-1);

    EXPECT_EQ(p->getFail(), -1);
}

TEST(Parentheses, get)
{
    vector<string> str;
    Parentheses* p = new Parentheses(str);

    EXPECT_EQ(p->getStr(), "p");

}

TEST(Parentheses, parentheses)
{
    vector<string> str;
    Parentheses* p = new Parentheses(str);

    EXPECT_EQ(p->getFail(), 0);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
