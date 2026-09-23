/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~((~x)|(~y));
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    // x^y = (x|y)&(~x|~y)
    // transfer | into &
    return ~(~x&~y)&~(x&y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    int t=!y;
    if(!x)return t;
    if(t)return 0; 
	int a=(x>>31),b=(y>>31);
	return !(a^b);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    // return 2;
    int op,x=v,now=0,tmp;
    
    op=(x>>16)>0;
    tmp=op<<4;
    x=x>>tmp;
    now=now|tmp;

    op=(x>>8)>0;
    tmp=op<<3;
    x=x>>tmp;
    now=now|tmp;

    op=(x>>4)>0;
    tmp=op<<2;
    x=x>>tmp;
    now=now|tmp;

    op=(x>>2)>0;
    tmp=op<<1;
    x=x>>tmp;
    now=now|tmp;

    op=(x>>1)>0;
    tmp=op;
    x=x>>tmp;
    now=now|tmp;
    
    return now;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int s=n<<3,t=m<<3;
    int a=(x>>s)&0xff,b=(x>>t)&0xff;
    return (x&(0xffffffff^(0xff<<s)^(0xff<<t)))^(a<<t)^(b<<s);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned x=v;
    x=((x&0x55555555)<<1)|((x>>1)&0x55555555);
    x=((x&0x33333333)<<2)|((x>>2)&0x33333333);
    x=((x&0x0f0f0f0f)<<4)|((x>>4)&0x0f0f0f0f);
    x=((x&0x00ff00ff)<<8)|((x>>8)&0x00ff00ff);
    x=((x&0x0000ffff)<<16)|((x>>16)&0x0000ffff);
    return x;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int op=x&0x80000000;
    x=x^op;
    x=x>>n;
    x=x^((!!op)<<(31u^n));
    return x;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int ans=0,op=0,tmp=0;

	//op:前面是否都是1 
	op=!((x^0xffff0000)>>16);
    ans=ans+(op<<4);
    x=(x>>((!op)<<4))&0x0000ffff;
    
    op=!((x>>8)^0x000000ff);
    ans=ans+(op<<3);
    x=(x>>((!op)<<3))&0x000000ff;

    op=!((x>>4)^0x0000000f);
    ans=ans+(op<<2);
    x=(x>>((!op)<<2))&0x0000000f;
    
    op=!((x>>2)^0x00000003);
    ans=ans+(op<<1);
    x=(x>>((!op)<<1))&0x00000003;

	op=!((x>>1)^0x00000001);
	ans=ans+op;
	x=(x>>(!op))&0x00000001; 
	
	ans=ans+x;
    return ans;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */

unsigned float_i2f(int u) {
	if(u==0)return 0u; 
    unsigned ans=0,x=u;
    if(u<0)x=-x,ans=0x80000000u;

    //l=-1
    unsigned l=0xffffffff;
    unsigned zzt=x;
    while(zzt)l+=1,zzt=zzt>>1;
    
    unsigned e=l+127;
    unsigned tmp=x-(1<<l);
	if(l<23)ans=ans|(tmp<<(23-l));
	else
    {
        unsigned step=l-23,lost=0,half=1<<(step-1);
        unsigned pwstep=1<<step;
        if(lost=tmp&(pwstep-1))
        {
            if((lost>half)|((lost==half)&(tmp>>step)))
                tmp=tmp+pwstep;
        }
        tmp=tmp>>step;
        if(tmp==0x00800000)e=e+1,tmp=0;
        ans=ans|tmp;
    }
    ans=ans|(e<<23);
    return ans;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    int e=(uf>>23)&0x000000ff;
    if(e==255)return uf;
    if(e) // 规格化
    {
		e=e+1; 
        return (uf&0x807fffff)|(e<<23);
    }
    //非规格化
    unsigned f=uf&0x007fffff;
    f=f<<1;
    return (uf&(1u<<31))|f;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    //uf2 uf1
    int op=uf2>>30;uf2=uf2&0x7fffffff;
    int E=(uf2>>20)-1023;
    if(E<0)return 0;
    if(E>=31)return 0x80000000;
    int val=0x40000000|((uf2&0x000fffff)<<20)|(uf1>>12);
    val=val>>(30-E);
    if(op)return -val;
    return val;
}//总共31位   1+10+20
//001111111111
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x>127)return 0x7f800000;
    if(x<-149)return 0;
    if(x>=-126)
    {
        int e=x+127;
        return e<<23;
    }
    //x < -127
    //x>=-149
    return 1<<(149+x);
}
//-126-23