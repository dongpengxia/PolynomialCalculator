# PolynomialHelper
Polynomial helper performs algebraic calculations on polynomials using a linked list.

To compile: g++ main.cpp Polynomial.cpp Term.cpp
	(make sure Term.h and Polynomial.h are in current directory)
To run: ./a.out sample_input.txt

Expected output for sample_input.txt:
Polynomial 1: f(x): 1x^3 + -2x^2 + 7x^1 + -5x^0
f(1) = 1
f(2) = 9
f(3) = 25
f(10) = 865

Polynomial 2: g(x): -2x^4 + 7x^2 + 10x^0
g(1) = 15
g(2) = 6
g(3) = -89
g(10) = -19290

f(x) + g(x) = -2x^4 + 1x^3 + 5x^2 + 7x^1 + 5x^0
(f + g)(1) = 16
(f + g)(2) = 15
(f + g)(3) = -64
(f + g)(10) = -18425

f(x) - g(x) = 2x^4 + 1x^3 + -9x^2 + 7x^1 + -15x^0
(f - g)(1) = -14
(f - g)(2) = 3
(f - g)(3) = 114
(f - g)(10) = 20155

f(x) * g(x) = -2x^7 + 4x^6 + -7x^5 + -4x^4 + 59x^3 + -55x^2 + 70x^1 + -50x^0
(f * g)(1) = 15
(f * g)(2) = 54
(f * g)(3) = -2225
(f * g)(10) = -16685850

f^5(x) = 1x^15 + -10x^14 + 75x^13 + -385x^12 + 1610x^11 + -5392x^10 + 15120x^9 + -35290x^8 + 68975x^7 + -111960x^6 + 148157x^5 + -156025x^4 + 123875x^3 + -67500x^2 + 21875x^1 + -3125x^0
f(x)^(g(5)) = Overflow Detected
(f^5)(2) = 59049
