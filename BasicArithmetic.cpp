#include<bits/stdc++.h>
using namespace std;

class bigint
{
  private:

    vector<int>num;
    int sign;
    static const int base = 1000000000;
    static const int base_digit = 9;

  public:
    static int givebase() {return base;}
    void operate(const string &s);
    bigint abs() const;
    bool operator>(const bigint &x)const;
    bool operator<(const bigint &x)const;
    bigint operator/(int x )const;
    void trim();
    bigint()
    {
      sign = 1;
    }
    
    bigint(const int &x )  // constructor with int
    {
      *this = x;
    }

    bigint(const long long int &x ) // constructor with long long 
    {
      *this = x;
    }
    bigint(const string &s)   // with string
    {
      operate(s);
    }

    void operator=(const bigint &x) // overloaded assignment operator
    {
      sign = x.sign;
      num  = x.num;
    }

    void operator=(const int val)    // for int
    {
      int x = val;
      if( x < 0 ) 
      {
        sign = - 1;
        x *= -1;
      }
      else sign = 1;

      while( x )
      {
        num.push_back( x % base );
        x /= base;
      }
    }
     
    void operator=(const long long int val) // for long long int 
    {
      long long int x = val;
      if( x < 0 ) 
      {
        sign = - 1;
        x *= -1;
      }
      else sign = 1;

      while( x )
      {
        num.push_back( x % base );
        x /= base;
      }
    }

    bigint operator-() const   // negation sign
    {
      bigint x = *this;
      x.sign = -sign;
      return (x);
    }

    bigint operator+( const bigint &x)  // binary + operator
    {
      if( x.sign * sign == -1 )       // check for sign
      {
        return (*this) - ( -x );     // else perform substraction with negation don't want to deal with sign :p
      }
      else
      {
        bigint ans = x;               // intialise as one operans so will have to work on only one operand
        int max_size = max( num.size() , x.num.size() ) , i , carry = 0;
        for( i = 0 ; i < max_size || carry != 0 ; i++ )
        {
          if( ans.num.size() == i )   // extend the vector(num) to fill number
          {
            ans.num.push_back(0);
          }
          ans.num[i] += carry + ( ( i < num.size() ) ? num[i] : 0 );

          if( ans.num[i] < base )      // carry check
           carry = 0;
          else 
          {
            ans.num[i] -= base;
            carry = 1;
          }
        }
        return ans;
      }
    }

    void operator+=(const bigint &x)
    {
      *this = *this + x;
    }

    bigint operator-( const bigint&x) const
    {
      if( sign * x.sign == - 1)
      {
        return (-x) + *this ; // again don't want headache of sign ;)
      }
      if( abs() > x.abs() )
      {
        bigint ans = *this;  //by taking the case when substarction will give positive ans , again don't want sign headache :p

        int max_size = x.num.size() , carry = 0 , i ;

        for( i = 0 ; i < max_size || carry ; ++i)
        {
          ans.num[i] -= ( carry + ( ( i < x.num.size() ) ? x.num[i] : 0 ) );
          if( ans.num[i] < 0 )
          {
            ans.num[i] += base;
            carry = 1;
          }
          else carry = 0;
        }
        ans.trim();
        return ans;
    }
      else return -( x - *this);
    }

    void operator-=(const bigint &x)
    {
      *this = *this - x;
    }

    bigint operator*(int x ) const
    {
      bigint ans = *this;
      if( x < 0 )
      {
        ans.sign *= -1;
        x = -x;
      }
      int max_size = ans.num.size() , i , carry = 0;
      for( i = 0 ; i < max_size || carry != 0 ; ++i)
      {
        if( i == max_size )
          ans.num.push_back(0);
        long long int mul = ans.num[i] * 1LL * x + carry;
        ans.num[i] = (int)(mul / base);
        carry      = (int)(mul % base);
      }
      ans.trim();
      return ans;
    }

    void operator*=(const int &x)
    {
      *this = *this * x;
    }

    friend pair<bigint , bigint>  bigint_division_mode(const bigint &x , const bigint &y)
    {
      int base1 = givebase();
      int factor = (base1 / y.num.back() + 1);
      bigint a = x*factor;
      bigint b = y*factor;
      bigint qut , rem;
      qut.num.resize( a.num.size() );
      int i , size_dsr = b.num.size();
      for( i = a.num.size() - 1 ; i >= 0 ; --i )
      {
        rem = rem*base;
        rem = rem + a.num[i];
        int c1 = ( rem.num.size() <= size_dsr ? 0 : rem.num[size_dsr] );
        int c2 = ( rem.num.size() <= size_dsr-1? 0 : rem.num[size_dsr-1]);
        int tmp = ( base*1LL*c1 + c2 ) / ( b.num.back() );
        rem = rem - (b*tmp);
        while( rem <0 )
        {
          rem = rem +  b;
          --tmp;
        }
        qut.num[i] = tmp;
      }
      if( x.sign == y.sign )
        qut.sign = 1;
      else qut.sign = -1;
      rem.sign = x.sign;
      qut.trim();
      rem.trim();
      return make_pair( qut , rem / factor );
    }

    
    bigint operator%(const bigint &x) const    // modulo operator
    {
      return bigint_division_mode(*this , x ).second;
    }

    bigint operator/(const bigint &x) const
    {
      return bigint_division_mode(*this , x).first;
    }

    friend pair<bigint , int> int_division_mode( const bigint &d , const int &val)
    {
      bigint y = d;
      int x = val;
      if( x < 0 )
      {
        y.sign *= -1;
        x = -x;
      }
      int i , max_size = y.num.size() , remainder = 0;
      long long int cur;
      for( i = max_size - 1 ; i >= 0 ; --i)
      {
        cur =  ( remainder * 1LL * base ) + y.num[i];
        y.num[i] = (int) ( cur / x );
        remainder    = (int) ( cur % x );
      }
      y.trim();
      return make_pair( y , remainder);
    }

    bigint operator /(const int &val)
    {
      return int_division_mode(*this,val).first;
    }

    bigint operator/=(const int &val)
    {
       *this = *this / val;
    } 

    int operator%(const int &val)
    {
      return int_division_mode(*this , val).second;
    }

    int operator%=(const int &val)
    {
      *this = (*this) % val;
    }






        




          

    

    
};

int main()
{
  
}  




          
           







      





