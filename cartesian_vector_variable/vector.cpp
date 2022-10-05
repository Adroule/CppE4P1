#include "vector.hh"



Vector::Vector(std::initializer_list<int> pCoordinates){
	for(int i=0; i<sizeof(pCoordinates)/sizeof(int); i++){
		this->coordinates[i]=std::data(pCoordinates)[i];
	}
}

Vector::Vector(size_t N){
	for(int i=0; i<N; i++){
		this->coordinates[i]=0;
	}
}

Vector::Vector(const Vector& v){
	for(int i=0; i<v.getTaille(); i++){
		this->coordinates[i]=v[i];
	}
}

Vector& Vector::operator=(const Vector& v1){
	for (int i = 0; i < this->taille; i++) {
		this->coordinates[i] = v1.coordinates[i];
	}
	return *this;
}

Vector Vector::operator+(const Vector& v1) const{
	Vector v3 = Vector{};
	for (int i = 0; i < this->taille; i++) {
		v3.coordinates[i] = v1.coordinates[i] + this->coordinates[i];
	}
	return v3;

}

Vector Vector::operator+(value v) const{
	Vector v3 = Vector{};
	for (int i = 0; i < this->taille; i++) {
		v3.coordinates[i] = v + this->coordinates[i];
	}
	return v3;
}

Vector& Vector::operator+=(const Vector& rhs){

	for(int i=0; i<this->taille; i++){
		this->coordinates[i]+=rhs.coordinates[i];
	}
	return *this;
	
}

Vector& Vector::operator+=(value n) {

	for (int i = 0; i < this->taille; i++) {
		this->coordinates[i] += n;
	}
	return *this;

}

Vector& Vector::operator-=(const Vector& rhs){

	for(int i=0; i<this->taille; i++){
		this->coordinates[i]-=rhs.coordinates[i];
	}
	return *this;
	
}

Vector& Vector::operator*=(value n) {

	for (int i = 0; i < this->taille; i++) {
		this->coordinates[i] *= n;
	}
	return *this;

}

Vector Vector::operator*(value n) const{

	for(int i=0; i<this->taille; i++){
		this->coordinates[i]*=n;
	}
	return *this;
	
}

value Vector::operator*(const Vector& rhs) const{
	int sum=0;
	for(int i=0; i<this->taille; i++){
		sum+=this->coordinates[i]*rhs.coordinates[i];
	}
	return sum;
	
}

value Vector::operator[](size_t n) const{
	return this->coordinates[n];
}

value& Vector::operator[](size_t n) {
	return this->coordinates[n];
}

value Vector::getTaille() const{
	return this->taille;
}

std::ostream& operator << (std::ostream& os, const Vector& v){
	os << "{";
	for(int i=0; i<v.getTaille(); i++){
		os << v[i] << ", ";
	}
	os << v[v.getTaille()-1] << "}";
	return os;
}
	

