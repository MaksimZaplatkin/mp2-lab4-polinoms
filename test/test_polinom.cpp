#include <gtest.h>
#include "polinom.h"
#include "monom.h"
// тесты мономов и полиномов
TEST(Polinom, can_multiply_correctly_polinom_polinom)
{
	Polinom p1("1x1y1z1");
	Polinom p2("5x5y5z5+2x2y2z2");
	Polinom p3("5x6y6z6+2x3y3z3");
	EXPECT_EQ(p3, p1 * p2);
}

TEST(Polinom, can_sum_correctly_polinom_polinom_first_test)
{
	Polinom p1("1x1y1z1");
	Polinom p2("2x1y1z1");
	Polinom p3("3x1y1z1");
	EXPECT_EQ(p3, p1 + p2);
}
TEST(Monom, can_create_monoms)
{
	EXPECT_NO_THROW(Monom m(1.0, 111));
}
TEST(Monom, can_insert_monoms)
{
	Polinom p("1x1y1z1");
	Monom m(1.0, 111);
	EXPECT_NO_THROW(p.set(m));
}
TEST(Monom, cand_delete_monoms)
{
	Polinom p("1x1y1z1");
	Monom m(1.0, 111);
	p.set(m);
	p.set(m);
	p.set(m);
	EXPECT_NO_THROW(p.erase(m));
	EXPECT_NO_THROW(p.erase(0));
}
TEST(Polinom, can_create_polinoms)
{
	EXPECT_NO_THROW(Polinom p("1x1y1z1"));
}
TEST(Polinom, can_multiply_polinom_const)
{
	double c = 1.2;
	Polinom p("1x1y1z1");
	EXPECT_NO_THROW(Polinom ans = p * c);
}
TEST(Polinom, cant_multiply_polinom_monom)
{
	Monom m(1.0, 111);
	Polinom p("1x1y1z1");
	EXPECT_NO_THROW(Polinom ans = p * m);
}
TEST(Polinom, can_multiply_polinoms)
{
	Polinom p("1x1y1z1");
	Polinom z("-1x1y1z1");
	EXPECT_NO_THROW(Polinom ans = p * z);
}
TEST(Polinom, can_sum_polinoms)
{
	Polinom p("1x1y1z1");
	Polinom z("-1x1y1z1");
	EXPECT_NO_THROW(Polinom ans = p + z);
}
TEST(Polinom, correct_multiply_polinom_const)
{
	Polinom p("1x1y1z1");
	double c = 5;
	Polinom p2("5x1y1z1");
	EXPECT_EQ(p2, p * c);
}
TEST(Polinom, correct_multiply_polinom_monom)
{
	Polinom p("1x1y1z1");
	Monom m(1, 111);
	Polinom p2("1x2y2z2");
	EXPECT_EQ(p2, p * m);
}

TEST(Polinom, can_sum_correctly_polinom_polinom_second_test)
{
	Polinom p1("1x1y1z1");
	Polinom p2("-1x1y1z1");
	Polinom p3("0x1y1z1");
	EXPECT_EQ(p3, p1 + p2);
}