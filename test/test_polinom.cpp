#include <gtest.h>
#include "polinom.h"
#include "monom.h"
// тесты мономов и полиномов

TEST(Polinom, can_sum_correctly_polinom_polinom_first_test)
{
	Polinom p1("xyz");
	Polinom p2("2xyz");
	Polinom p3("3xyz");
	EXPECT_EQ(p3, p1 + p2);
}
TEST(Monom, can_create_monoms)
{
	EXPECT_NO_THROW(Monom m(1.0, 111));
}
TEST(Monom, can_insert_monoms)
{
	Polinom p("xyz");
	Monom m(1.0, 111);
	EXPECT_NO_THROW(p.set(m));
}
TEST(Monom, cand_delete_monoms)
{
	Polinom p("xyz");
	Monom m(1.0, 111);
	p.set(m);
	p.set(m);
	p.set(m);
	EXPECT_NO_THROW(p.erase(m));
	EXPECT_NO_THROW(p.erase(0));
}
TEST(Polinom, can_create_polinoms)
{
	EXPECT_NO_THROW(Polinom p("xyz"));
}
TEST(Polinom, can_multiply_polinom_const)
{
	double c = 1.2;
	Polinom p("xyz");
	EXPECT_NO_THROW(Polinom ans = p * c);
}
TEST(Polinom, cant_multiply_polinom_monom)
{
	Monom m(1.0, 111);
	Polinom p("xyz");
	EXPECT_NO_THROW(Polinom ans = p * m);
}
TEST(Polinom, can_multiply_polinoms)
{
	Polinom p("xyz");
	Polinom z("-xyz");
	EXPECT_NO_THROW(Polinom ans = p * z);
}
TEST(Polinom, can_sum_polinoms)
{
	Polinom p("xyz");
	Polinom z("-xyz");
	EXPECT_NO_THROW(Polinom ans = p + z);
}
TEST(Polinom, correct_multiply_polinom_const)
{
	Polinom p("xyz");
	double c = 5;
	Polinom p2("5xyz");
	EXPECT_EQ(p2, p * c);
}
TEST(Polinom, correct_multiply_polinom_monom)
{
	Polinom p("xyz");
	Monom m(1, 111);
	Polinom p2("x^2y^2z^2");
	EXPECT_EQ(p2, p * m);
}

TEST(Polinom, can_sum_correctly_polinom_polinom_second_test)
{
	Polinom p1("xyz");
	Polinom p2("-xyz");
	Polinom p3("0xyz");
	EXPECT_EQ(p3, p1 + p2);
}