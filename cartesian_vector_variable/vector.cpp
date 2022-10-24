#include "vector.hh"


Vector::Vector(std::initializer_list<value> pCoordinates) : coordinates{ std::make_unique<value[]>(pCoordinates.size()) }, taille{ pCoordinates.size() } {
	for (int i = 0; i < pCoordinates.size(); i++) {
		this->coordinates[i] = std::data(pCoordinates)[i];
	}
}

Vector::Vector(const size_t N) : coordinates{ std::make_unique<value[]>(N) }, taille{ N } {
	for (int i = 0; i < N; i++) {
		this->coordinates[i] = value(0);
	}
}

Vector::Vector(const Vector& v) {
	this->taille = v.size();
	this->coordinates = std::make_unique<value[]>(this->taille);
	for (int i = 0; i < v.size(); i++) {
		this->coordinates[i] = v[i];
	}
}

size_t Vector::size() const {
	return this->taille;
}

Vector& Vector::operator=(const Vector& v1) {
	this->taille = v1.size();
	this->coordinates = std::make_unique<value[]>(this->taille);
	for (int i = 0; i < this->taille; i++) {
		this->coordinates[i] = v1.coordinates[i];
	}
	return *this;
}

Vector Vector::operator+(const Vector& v1) const {
	if (v1.size() != this->size())
		throw std::runtime_error("Incompatible size");
	Vector v3 = Vector(v1.taille);
	for (int i = 0; i < this->taille; i++) {
		v3.coordinates[i] = v1.coordinates[i] + this->coordinates[i];
	}
	return v3;

}

Vector Vector::operator+(const value v) const {
	Vector v3 = Vector(this->taille);
	for (int i = 0; i < this->taille; i++) {
		v3.coordinates[i] = v + this->coordinates[i];
	}
	return v3;
}

Vector& Vector::operator+=(const Vector& rhs) {
	if (rhs.size() != this->size())
		throw std::runtime_error("Incompatible size");

	for (int i = 0; i < this->taille; i++) {
		this->coordinates[i] += rhs.coordinates[i];
	}
	return *this;

}

Vector& Vector::operator+=(value n) {

	for (int i = 0; i < this->taille; i++) {
		this->coordinates[i] += n;
	}
	return *this;

}

Vector Vector::operator-(const value v) const {
	Vector v3 = Vector(this->taille);
	for (int i = 0; i < this->taille; i++) {
		v3.coordinates[i] = v - this->coordinates[i];
	}
	return v3;
}

Vector& Vector::operator-=(const Vector& rhs) {
	if (rhs.size() != this->size())
		throw std::runtime_error("Incompatible size");

	for (int i = 0; i < this->taille; i++) {
		this->coordinates[i] -= rhs.coordinates[i];
	}
	return *this;

}

Vector& Vector::operator-=(value n) {
	for (int i = 0; i < this->taille; i++) {
		this->coordinates[i] -= n;
	}
	return *this;

}

Vector& Vector::operator*=(value n) {

	for (int i = 0; i < this->taille; i++) {
		this->coordinates[i] *= n;
	}
	return *this;

}

Vector Vector::operator*(value n) const {

	for (int i = 0; i < this->taille; i++) {
		this->coordinates[i] *= n;
	}
	return *this;

}

value Vector::operator*(const Vector& rhs) const {
	if (rhs.size() != this->size())
		throw std::runtime_error("Incompatible size");
	value sum = 0;
	for (int i = 0; i < this->taille; i++) {
		sum += this->coordinates[i] * rhs.coordinates[i];
	}
	return sum;

}

Vector Vector::operator/(const value v) const {
	Vector v3 = Vector(this->taille);
	for (int i = 0; i < this->taille; i++) {
		v3.coordinates[i] = this->coordinates[i]/v;
	}
	return v3;
}


value Vector::operator[](size_t n) const {
	return this->coordinates[n];
}

value& Vector::operator[](size_t n) {
	return this->coordinates[n];
}



std::ostream& operator << (std::ostream& os, const Vector& v) {
	os << "{";
	for (int i = 0; i < v.size()-1; i++) {
		os << v[i] << ", ";
	}
	os << v[v.size() - 1] << "}";
	return os;
}
