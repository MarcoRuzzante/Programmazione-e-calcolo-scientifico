
#include <iostream>
#include <concepts> 

template<typename I> requires std::integral<I>
class rational {
    I num_;
    I den_;

public:

    rational()
        : num_(I{0}), den_(I{1})
    {}

    rational(const I& px, const I& py) {

        //Normalizzazione e calcolo MCD
        I a = px;
        I b = py;
        
        if (a < I{0}) a = -a;
        if (b < I{0}) b = -b;
        
        while (b != I{0}) {
            I temp = b;
            b = a % b;
            a = temp;
        }
        I MCD = a; 
        
        if (MCD == I{0}) {      //se MCD = 0 allora è 0/0
            num_ = I{0};
            den_ = I{0};
        } 

        else {
            I n = px / MCD;
            I d = py / MCD;
            
            if (d < I{0}) {
                n = -n;
                d = -d;
            } 
            
            num_ = n;
            den_ = d;
        }
    
    }

    I num() const { return num_; }
    I den() const { return den_; }

    rational& operator+=(const rational& other) {

        if (den_ == I{0} || other.den_ == I{0}) {

            // NaN + qualcosa = NaN
            if (num_ == I{0} && den_ == I{0}) return *this;         //è già 0/0

            if (other.num_ == I{0} && other.den_ == I{0}) { 
                num_ = I{0}; den_ = I{0};                           //devo avere 0/0 per stampare NaN
                return *this; 
            }
            
            if (den_ == I{0} && other.den_ == I{0}) {
                // Se ho +Inf - Inf
                if (num_ != other.num_) { 
                    num_ = I{0};                                    //devo avere 0/0 per stampare NaN
                    den_ = I{0}; 
                }
                return *this;
            }
            
            // x + Inf = Inf
            if (other.den_ == I{0}) { 
                num_ = other.num_; 
                den_ = I{0}; 
                return *this; 
            }
            
            // Inf + x =Inf
            return *this;
        }

        I n = num_ * other.den_ + other.num_ * den_;
        I d = den_ * other.den_;
        
        *this = rational(n, d);                             //per normalizzare
        return *this;
    }

    rational operator+(const rational& other) const {
        rational ret = *this;
        ret += other;
        return ret;
    }

    rational& operator-=(const rational& other) {
        rational opp(-other.num_, other.den_);
        *this += opp;
        return *this;
    }

    rational operator-(const rational& other) const {
        rational ret = *this;
        ret -= other;
        return ret;
    }

    rational& operator*=(const rational& other) {

        if (den_ == I{0} || other.den_ == I{0}) {
            // 0 * Inf
            if (num_ == I{0} || other.num_ == I{0}) { 
                num_ = I{0}; 
                den_ = I{0}; 
                return *this; 
            }
            
            else{
                num_ *= other.num_;
                den_ = I{0};
                *this = rational(num_, den_); //per i segni
                return *this;
            }
        }

        I n = num_ * other.num_;
        I d = den_ * other.den_;
        *this = rational(n, d);
        return *this;
    }

    rational operator*(const rational& other) const {
        rational ret = *this;
        ret *= other;
        return ret;
    }

    
    rational& operator/=(const rational& other) {       //(a/b)/(c/d) = ad/bc
        rational reciproco(other.den_, other.num_);
        *this *= reciproco;
        return *this;
    }

    rational operator/(const rational& other) const {
        rational ret = *this;
        ret /= other;
        return ret;
    }
};


template<typename I>
std::ostream&
operator<<(std::ostream& os, const rational<I>& r){

    if (r.den() == I{0}) {

        if (r.num() == I{0}) os << "NaN";

        else {
            if (r.num() > I{0}) os << "+Inf";
            else os << "-Inf";
        }

    } 

    else os << r.num() << "/" << r.den();
    return os;
}

int main(void){

    rational<int> default_val;
    std::cout << "Costruttore di default:\t" << default_val<<"\n\n";

    rational<int> r1(4, 8);
    std::cout << "4/8 diventa:\t" << r1 << "\n";

    rational<int> r2(3, -6);
    std::cout << "3/-6 diventa:\t" << r2 << "\n";

    rational<int> r3(-5, -15);
    std::cout << "-5/-15 diventa:\t" << r3 << "\n";

    rational<int> r4(0, -52);
    std::cout << "0/-52 diventa:\t" << r4 << "\n\n";

   

    rational<int> a(1, 2);
    rational<int> b(1, 3);
    std::cout << "a=" << a << "\tb=" << b << "\n";
    
    rational<int> somma = a + b;
    std::cout << "Somma: " << a << " + " << b << " = " << somma << "\n";

    rational<int> sottrazione = a - b;
    std::cout << "Sottrazione: " << a << " - " << b << " = " << sottrazione << "\n";

    rational<int> molt = a * b;
    std::cout << "Moltiplicazione:    " << a << " * " << b << " = " << molt << "\n";

    rational<int> divisione = a / b;
    std::cout << "Divisione:   " << a << " / " << b << " = " << divisione << "\n\n";

    

    rational<int> r5(4, 0);
    std::cout << "4/0  diventa:\t" << r5 << "\n";

    rational<int> r6(-4, 0);
    std::cout << "-4/0 diventa:\t" << r6 << "\n";

    rational<int> r7(0, 0);
    std::cout << "0/0 diventa:\t" << r7 << "\n\n";



    rational<int> r8 = r5 + a;
    std::cout << "Inf + a = " << r8 << "\n";

    rational<int> r9 = r5 * r6;
    std::cout << "Inf*(-Inf) = " << r9 << "\n";

    rational<int> r10 = r5 + r6;
    std::cout << "Inf - Inf = " << r10 << "\n";

    rational<int> r11 = r7 + a;
    std::cout << "NaN + a: = " << r11 << "\n";

    rational<int> r12 = r4 * r5;
    std::cout << "0*Inf = " << r12 << "\n";

    
    return 0;
}