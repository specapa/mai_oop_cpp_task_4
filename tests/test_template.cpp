#include <gtest/gtest.h>
#include "Point.hpp"
#include "Rectangle.hpp"
#include "Square.hpp"
#include "Trapezoid.hpp"
#include <sstream>
#include <cmath>

// ============= Point Tests =============

TEST(PointTest, DefaultConstructor) {
    Point<int> p;
    EXPECT_EQ(p.x, 0);
    EXPECT_EQ(p.y, 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, 4.2);
    EXPECT_DOUBLE_EQ(p.x, 3.5);
    EXPECT_DOUBLE_EQ(p.y, 4.2);
}

TEST(PointTest, CopyConstructor) {
    Point<int> p1(5, 10);
    Point<int> p2(p1);
    EXPECT_EQ(p2.x, 5);
    EXPECT_EQ(p2.y, 10);
}

TEST(PointTest, AssignmentOperator) {
    Point<int> p1(7, 9);
    Point<int> p2;
    p2 = p1;
    EXPECT_EQ(p2.x, 7);
    EXPECT_EQ(p2.y, 9);
}

TEST(PointTest, EqualityOperator) {
    Point<int> p1(3, 4);
    Point<int> p2(3, 4);
    Point<int> p3(5, 6);
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, AdditionOperator) {
    Point<int> p1(2, 3);
    Point<int> p2(4, 5);
    Point<int> result = p1 + p2;
    EXPECT_EQ(result.x, 6);
    EXPECT_EQ(result.y, 8);
}

TEST(PointTest, SubtractionOperator) {
    Point<int> p1(10, 8);
    Point<int> p2(3, 2);
    Point<int> result = p1 - p2;
    EXPECT_EQ(result.x, 7);
    EXPECT_EQ(result.y, 6);
}

TEST(PointTest, DivisionOperator) {
    Point<double> p(10.0, 20.0);
    Point<double> result = p / 2.0;
    EXPECT_DOUBLE_EQ(result.x, 5.0);
    EXPECT_DOUBLE_EQ(result.y, 10.0);
}

TEST(PointTest, Distance) {
    Point<double> p1(0.0, 0.0);
    Point<double> p2(3.0, 4.0);
    EXPECT_DOUBLE_EQ(p1.distance(p2), 5.0);
}

TEST(PointTest, OutputStream) {
    Point<int> p(5, 7);
    std::ostringstream oss;
    oss << p;
    EXPECT_EQ(oss.str(), "(5, 7)");
}

TEST(PointTest, InputStream) {
    Point<int> p;
    std::istringstream iss("10 20");
    iss >> p;
    EXPECT_EQ(p.x, 10);
    EXPECT_EQ(p.y, 20);
}

// ============= Rectangle Tests =============

TEST(RectangleTest, DefaultConstructor) {
    Rectangle<double> rect;
    EXPECT_NO_THROW(rect.Print(std::cout));
}

TEST(RectangleTest, ReadValidRectangle) {
    Rectangle<double> rect;
    std::istringstream iss("0 0 4 0 4 3 0 3");
    EXPECT_NO_THROW(rect.Read(iss));
}

TEST(RectangleTest, CenterCalculation) {
    Rectangle<double> rect;
    std::istringstream iss("0 0 4 0 4 2 0 2");
    rect.Read(iss);
    auto center = rect.Center();
    EXPECT_DOUBLE_EQ(center.first, 2.0);
    EXPECT_DOUBLE_EQ(center.second, 1.0);
}

TEST(RectangleTest, AreaCalculation) {
    Rectangle<double> rect;
    std::istringstream iss("0 0 4 0 4 3 0 3");
    rect.Read(iss);
    double area = static_cast<double>(rect);
    EXPECT_DOUBLE_EQ(area, 12.0);
}

TEST(RectangleTest, EqualityOperator) {
    Rectangle<double> rect1, rect2;
    std::istringstream iss1("0 0 4 0 4 3 0 3");
    std::istringstream iss2("0 0 4 0 4 3 0 3");
    rect1.Read(iss1);
    rect2.Read(iss2);
    EXPECT_TRUE(rect1 == rect2);
}

TEST(RectangleTest, PrintOutput) {
    Rectangle<double> rect;
    std::istringstream iss("0 0 2 0 2 1 0 1");
    rect.Read(iss);
    std::ostringstream oss;
    rect.Print(oss);
    EXPECT_FALSE(oss.str().empty());
}

// ============= Square Tests =============

TEST(SquareTest, DefaultConstructor) {
    Square<double> sq;
    EXPECT_NO_THROW(sq.Print(std::cout));
}

TEST(SquareTest, ReadValidSquare) {
    Square<double> sq;
    std::istringstream iss("0 0 2 0 2 2 0 2");
    EXPECT_NO_THROW(sq.Read(iss));
}

TEST(SquareTest, CenterCalculation) {
    Square<double> sq;
    std::istringstream iss("0 0 4 0 4 4 0 4");
    sq.Read(iss);
    auto center = sq.Center();
    EXPECT_DOUBLE_EQ(center.first, 2.0);
    EXPECT_DOUBLE_EQ(center.second, 2.0);
}

TEST(SquareTest, AreaCalculation) {
    Square<double> sq;
    std::istringstream iss("0 0 3 0 3 3 0 3");
    sq.Read(iss);
    double area = static_cast<double>(sq);
    EXPECT_DOUBLE_EQ(area, 9.0);
}

TEST(SquareTest, EqualityOperator) {
    Square<double> sq1, sq2;
    std::istringstream iss1("0 0 5 0 5 5 0 5");
    std::istringstream iss2("0 0 5 0 5 5 0 5");
    sq1.Read(iss1);
    sq2.Read(iss2);
    EXPECT_TRUE(sq1 == sq2);
}

TEST(SquareTest, UnitSquare) {
    Square<int> sq;
    std::istringstream iss("0 0 1 0 1 1 0 1");
    sq.Read(iss);
    double area = static_cast<double>(sq);
    EXPECT_DOUBLE_EQ(area, 1.0);
}

// ============= Trapezoid Tests =============

TEST(TrapezoidTest, DefaultConstructor) {
    Trapezoid<double> trap;
    EXPECT_NO_THROW(trap.Print(std::cout));
}

TEST(TrapezoidTest, ReadValidTrapezoid) {
    Trapezoid<double> trap;
    std::istringstream iss("0 0 4 0 3 2 1 2");
    EXPECT_NO_THROW(trap.Read(iss));
}

TEST(TrapezoidTest, CenterCalculation) {
    Trapezoid<double> trap;
    std::istringstream iss("0 0 4 0 3 2 1 2");
    trap.Read(iss);
    auto center = trap.Center();
    EXPECT_GT(center.first, 0.0);
    EXPECT_GT(center.second, 0.0);
}

TEST(TrapezoidTest, AreaCalculation) {
    Trapezoid<double> trap;
    std::istringstream iss("0 0 6 0 5 3 1 3");
    trap.Read(iss);
    double area = static_cast<double>(trap);
    EXPECT_GT(area, 0.0);
}

TEST(TrapezoidTest, EqualityOperator) {
    Trapezoid<double> trap1, trap2;
    std::istringstream iss1("0 0 4 0 3 2 1 2");
    std::istringstream iss2("0 0 4 0 3 2 1 2");
    trap1.Read(iss1);
    trap2.Read(iss2);
    EXPECT_TRUE(trap1 == trap2);
}

TEST(TrapezoidTest, IsoscelesTrapezoid) {
    Trapezoid<double> trap;
    std::istringstream iss("0 0 4 0 3 2 1 2");
    EXPECT_NO_THROW(trap.Read(iss));
}

// ============= Integration Tests =============

TEST(IntegrationTest, DifferentTypesInt) {
    Point<int> p(5, 10);
    EXPECT_EQ(p.x, 5);
    EXPECT_EQ(p.y, 10);
}

TEST(IntegrationTest, DifferentTypesFloat) {
    Point<float> p(3.14f, 2.71f);
    EXPECT_FLOAT_EQ(p.x, 3.14f);
    EXPECT_FLOAT_EQ(p.y, 2.71f);
}

TEST(IntegrationTest, MultipleShapes) {
    Rectangle<double> rect;
    Square<double> sq;
    Trapezoid<double> trap;
    
    std::istringstream iss_rect("0 0 4 0 4 2 0 2");
    std::istringstream iss_sq("0 0 3 0 3 3 0 3");
    std::istringstream iss_trap("0 0 4 0 3 2 1 2");
    
    EXPECT_NO_THROW(rect.Read(iss_rect));
    EXPECT_NO_THROW(sq.Read(iss_sq));
    EXPECT_NO_THROW(trap.Read(iss_trap));
}

// ============= Edge Cases Tests =============

TEST(EdgeCaseTest, ZeroAreaRectangle) {
    Rectangle<double> rect;
    std::istringstream iss("0 0 0 0 0 0 0 0");
    EXPECT_ANY_THROW(rect.Read(iss));
}

TEST(EdgeCaseTest, PointDistanceZero) {
    Point<double> p1(5.0, 5.0);
    Point<double> p2(5.0, 5.0);
    EXPECT_DOUBLE_EQ(p1.distance(p2), 0.0);
}

TEST(EdgeCaseTest, NegativeCoordinates) {
    Point<int> p(-5, -10);
    EXPECT_EQ(p.x, -5);
    EXPECT_EQ(p.y, -10);
}

TEST(EdgeCaseTest, LargeCoordinates) {
    Point<double> p(1e6, 1e6);
    EXPECT_DOUBLE_EQ(p.x, 1e6);
    EXPECT_DOUBLE_EQ(p.y, 1e6);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}