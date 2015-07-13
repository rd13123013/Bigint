#include<bits/stdc++.h>
using namespace std;

class bigint
{
  private:

    vector<int>num;
    int sign;
    const int base = 1000000000;
    const int base_digit = 9;

  public:
    int givebase() {return base};
    void operate(const string &s);
    bigint abs() const;
    bool operator>(const bigint &x)const;
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

    pair<bigint , bigint>  disvison_mod(const bigint &x , const bigint &y)
    {
      base = givebase();
      int factor = (base / y.num.back() + 1);
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
          

    

    
};

int main()
{
  
}  




          
           







      





