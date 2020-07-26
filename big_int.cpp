#include "big_int.h"

static u_int ft_abs(int num) {
	if (num > 0)
		return ((u_int) num);
	else {
		num++;
		num *= -1;
		return ((u_int) num + 1);
	}
}

static u_int ft_max(u_int left, u_int right) {
	return (left > right ? left : right);
}

BigInt::BigInt() {
	num.reserve(DEFAULT_NUM_SIZE);
	buff_size = DEFAULT_NUM_SIZE;
	num_size = 1;
	num.push_back(0);
	sign = false;
}

BigInt::BigInt(int n) {
	num.reserve(DEFAULT_NUM_SIZE);
	buff_size = DEFAULT_NUM_SIZE;
	num_size = 1;
	num.push_back(ft_abs(n));
	sign = n < 0;
}

BigInt::BigInt(const BigInt &copied) {
	num.reserve(copied.buff_size);
	buff_size = copied.buff_size;
	num_size = copied.num_size;
	num.resize(num_size);
	for (size_t i = 0; i < num_size; ++i)
		num[i] = copied.num[i];
	sign = copied.sign;
}

BigInt::BigInt(BigInt &&moved) noexcept {
	num.reserve(moved.buff_size);
	buff_size = moved.buff_size;
	num_size = moved.num_size;
	num.resize(num_size);
	for (size_t i = 0; i < num_size; ++i)
		num[i] = moved.num[i];
	sign = moved.sign;
	moved.buff_size = 0;
	moved.num_size = 0;
	moved.sign = false;
	moved.num.clear();
}

BigInt::~BigInt() {
	this->num.clear();
	this->sign = false;
	this->num_size = 0;
	this->buff_size = 0;
	std::cout << "~" << std::endl;
}

BigInt &BigInt::operator=(const BigInt &copied) {
	if (this == &copied)
		return (*this);
	buff_size = copied.buff_size;
	num_size = copied.num_size;
	sign = copied.sign;
	num.reserve(buff_size);
	num.resize(num_size);
	for (size_t i = 0; i < num_size; ++i)
		num[i] = copied.num[i];
	return (*this);
}

BigInt &BigInt::operator=(BigInt &&moved) noexcept {
	if (this == &moved)
		return (*this);
	buff_size = moved.buff_size;
	num_size = moved.num_size;
	sign = moved.sign;
	num.reserve(buff_size);
	num.resize(num_size);
	for (size_t i = 0; i < num_size; ++i)
		num[i] = moved.num[i];
	moved.num_size = 0;
	moved.buff_size = 0;
	moved.sign = false;
	moved.num.clear();
	return (*this);
}

BigInt &BigInt::operator=(const int &copied) {
	sign = copied < 0;
	num[0] = ft_abs(copied);
	for (size_t i = 1; i < num_size; ++i)
		num[i] = 0;
	num_size = 1;
	return (*this);
}

BigInt &BigInt::operator=(int &&moved) noexcept {
	sign = moved < 0;
	num[0] = ft_abs(moved);
	for (size_t i = 1; i < num_size; ++i)
		num[i] = 0;
	num_size = 1;
	moved = 0;
	return (*this);
}

bool BigInt::operator==(const BigInt &other) const {
	if (sign != other.sign)
		return false;
	else if (num_size != other.num_size)
		return (false);
	else
		for (size_t i = 0; i < num_size; ++i)
			if (num[i] != other.num[i])
				return (false);
	return (true);
}

bool BigInt::operator!=(const BigInt &other) const {
	return !(*this == other);
}

bool BigInt::operator<(const BigInt &other) const {
	if (sign != other.sign)
		return (sign);
	else if (num_size > other.num_size)
		return (sign);
	else if (num_size < other.num_size)
		return (!sign);
	else
		for (size_t i = num_size; i > 0; --i)
			if (num[i - 1] < other.num[i - 1])
				return (true);
			else if (num[i - 1] > other.num[i - 1])
				return (false);
	return false;
}

bool BigInt::operator<=(const BigInt &other) const {
	return (*this == other || *this < other);
}

bool BigInt::operator>(const BigInt &other) const {
	return (!(*this <= other));
}

bool BigInt::operator>=(const BigInt &other) const {
	return (!(*this < other));
}

bool BigInt::operator==(const int &other) const {
	if (num_size > 1)
		return (false);
	else if (sign != (other < 0))
		return (false);
	else
		return (num[0] == ft_abs(other));
}

bool BigInt::operator!=(const int &other) const {
	return (!(*this == other));
}

bool BigInt::operator<(const int &other) const {
	bool o_sign;

	o_sign = other < 0;
	if (sign != o_sign)
		return (sign > o_sign);
	else if (num_size > 1)
		return (sign);
	else
		return (num[0] < ft_abs(other));
}

bool BigInt::operator<=(const int &other) const {
	return (*this == other || *this < other);
}

bool BigInt::operator>(const int &other) const {
	return (!(*this <= other));
}

bool BigInt::operator>=(const int &other) const {
	return (!(*this < other));
}

void BigInt::check_size() {
	while (buff_size < num_size || buff_size - num_size < 4) {
		buff_size += 4;
		num.reserve(buff_size);
	}
}

BigInt BigInt::add(const BigInt &left, const BigInt &right) {
	BigInt res;

	res.sign = left.sign;
	res.num_size = ft_max(left.num_size, right.num_size) + 1;
	res.check_size();
	res.num.resize(res.num_size, 0);
	for (size_t i = 0; i < res.num_size; ++i) {
		if (res.num[i] && (left.num[i] == MAX_UNIT_VALUE || right.num[i] == MAX_UNIT_VALUE))
			res.num[i + 1] = res.num[i]--;
		if (MAX_UNIT_VALUE - left.num[i] < right.num[i])
			res.num[i + 1] += 1;
		res.num[i] = left.num[i] + right.num[i];
	}
	return (res);
}

BigInt BigInt::reverse() const {
	BigInt res(*this);

	for (size_t i = 0; i < num_size; ++i)
		res.num[i] = MAX_UNIT_VALUE - num[i];
	return res;
}

BigInt BigInt::operator+(const BigInt &other) const {
	BigInt res;

	if (sign == other.sign) {
		res = add(*this, other);
	} else {
		BigInt left_abs = my_abs(*this);
		BigInt right_abs = my_abs(other);
		if (left_abs < right_abs) {
			res = add(left_abs, right_abs.reverse());
			if (other.sign)
				res = res.reverse();
			res.sign = other.sign;
		} else {
			res = add(left_abs.reverse(), right_abs);
			if (sign)
				res = res.reverse();
			res.sign = sign;
		}
	}
	res.erase_extra_zeros();
	if (my_abs(res) == 0)
		res.sign = false;
	return res;
}

BigInt BigInt::operator-() const {
	BigInt res(*this);
	res.sign = !res.sign;
	return res;
}

BigInt BigInt::operator-(const BigInt &other) const {
	return (*this + (-other));
}

BigInt BigInt::operator+(const int &other) const {
	BigInt right(other);
	return *this + right;
}

BigInt BigInt::operator-(const int &other) const {
	return *this + (-other);
}

void BigInt::operator+=(const BigInt &other) {
	*this = *this + other;
}

std::ostream &operator<<(std::ostream &out, const BigInt &big_int) {
	if (big_int.sign)
		out << "-";
	for (size_t i = big_int.num_size; i > 0; --i)
		out << big_int.num[i - 1] << " ";
	out << std::endl;
	return (out);
}

std::istream &operator>>(std::istream &in, BigInt &big_int) {
	char	ch;
	u_int sign;

	big_int = 0;
	sign = in.peek();
	if (sign == 45 || sign == 43)
		in.get();
	while (in.peek()){
		in.get(ch);
		if (ch < 48 || ch > 57)
			break ;
		else{
			big_int *= 10;
			big_int += (int)(ch - '0');
		}
	}
	if (sign == 45 || sign == 43)
		big_int.sign = sign == 45;
	return (in);
}

BigInt BigInt::my_abs(const BigInt &num) {
	BigInt res = num;
	res.sign = false;
	return res;
}

void BigInt::erase_extra_zeros() {
	while (num.end() != num.begin() && *num.end() == 0)
		num.pop_back();
	num_size = num.size();
}

BigInt BigInt::operator*(const int &other) const {
	BigInt res;
	size_t lim;
	int oth = other;

	if (other == 0)
		res = 0;
	else if (other * (-1) == other) {
		res.sign = !res.sign;
		res = *this << 1;
	} else {
		if (other < 0)
			oth *= -1;
		lim = (size_t) oth;
		res = 0;
		for (size_t i = 0; i < lim; ++i)
			res += *this;
		res.sign = other < 0 == !sign;
	}
	return res;
}

BigInt BigInt::operator*(const u_int &other) const {
	BigInt res;
	size_t lim;

	if (other == 0)
		res = 0;
	else {
		lim = (size_t) other;
		res = 0;
		for (size_t i = 0; i < lim; ++i)
			res += *this;
		res.sign = sign;
	}
	return res;
}

BigInt BigInt::operator*(const BigInt &other) const {
	BigInt res;
	BigInt oth;

	if (other == 0)
		res = 0;
	else {
		res = 0;
		for (size_t i = 0; i < other.num_size; ++i)
			res += (*this * other.num[i]) << i;
		res.sign = other.sign == !sign;
	}
	return res;
}

BigInt BigInt::operator/(const u_int &other) const {
	BigInt res;
	BigInt ths = my_abs(*this);
	BigInt oth = my_abs(BigInt(other));

	res = 0;
	while (ths > oth){
		ths -= oth;
		++res;
	}
	res = other < 0 == !sign;
	return res;
}

BigInt BigInt::operator/(const BigInt &other) const {
	BigInt res;
	BigInt ths = my_abs(*this);
	BigInt oth = my_abs(other);

	res = 0;
	while (ths > oth){
		ths -= oth;
		++res;
	}
	res = other.sign == !sign;
	return res;
}

void BigInt::operator-=(const BigInt &other) {
	*this = *this - other;
}

void BigInt::operator*=(const BigInt &other) {
	*this = *this * other;
}

void BigInt::operator++() {
	*this = *this + 1;
}

BigInt BigInt::operator<<(const u_int &other) const {
	BigInt res = *this;
	auto oth = (size_t) other;

	res.num_size += oth;
	res.check_size();
	res.num.resize(res.num_size);
	for (size_t i = res.num_size - oth; i > 0; --i)
		res.num[i + oth - 1] = res.num[i - 1];
	for (size_t i = 0; i < oth; ++i)
		res.num[i] = 0;
	return res;
}
