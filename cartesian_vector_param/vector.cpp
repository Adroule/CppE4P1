#include "vector.hh"



Vector::Vector(std::initializer_list<value> pCoordinates) {
	for (int i = 0; i < NDIM; i++) {
		this->coordinates[i] = std::data(pCoordinates)[i];
	}
}

Vector::Vector() {
	for (int i = 0; i < NDIM; i++) {
		this->coordinates[i] = value(0);
	}
}


Vector Vector::operator+(const Vector& v1) {
	Vector v3 = Vector{};
	for (int i = 0; i < NDIM; i++) {
		v3.coordinates[i] = v1.coordinates[i] + this->coordinates[i];
	}
	return v3;

}

Vector& Vector::operator+=(const Vector& rhs) {

	for (int i = 0; i < NDIM; i++) {
		this->coordinates[i] += rhs.coordinates[i];
	}
	return *this;

}

Vector& Vector::operator+=(const value& n) {

	for (int i = 0; i < NDIM; i++) {
		this->coordinates[i] += n;
	}
	return *this;

}

Vector& Vector::operator-=(const Vector& rhs) {

	for (int i = 0; i < NDIM; i++) {
		this->coordinates[i] -= rhs.coordinates[i];
	}
	return *this;

}

Vector& Vector::operator*=(const value& n) {

	for (int i = 0; i < NDIM; i++) {
		this->coordinates[i] *= n;
	}
	return *this;

}

Vector& Vector::operator*(const value& n) {

	for (int i = 0; i < NDIM; i++) {
		this->coordinates[i] *= n;
	}
	return *this;

}

value Vector::operator*(const Vector& rhs) {
	value sum = 0;
	for (int i = 0; i < NDIM; i++) {
		sum += this->coordinates[i] * rhs.coordinates[i];
	}
	return sum;

}

value Vector::operator[](const int n) const {
	return this->coordinates[n];
}

value& Vector::operator[](const int n) {
	return this->coordinates[n];
}

std::ostream& operator << (std::ostream& os, const Vector& v) {
	os << "{";
	for (int i = 0; i < NDIM - 1; i++) {
		os << v[i] << ", ";
	}
	os << v[NDIM - 1] << "}";
	return os;
}