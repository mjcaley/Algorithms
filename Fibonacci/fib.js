// Renault's code!
function pisano(m)
// Period is 4k mod F(2k) and 8k+4 mod F(2k+1)
{
    var a = 0, b = 1, c = (a+b)%m, k = 1, z;
    while(b != 0)
    {
        a = b; b = c; c = (a+b)%m;k++;
    }
    z=1;
    if (k%2 == 1)
    {
        k = k*4; z = 4;
    }
    else {
        if (c != 1)
        {
            k = k*2; z = 2;
        }
    }
    if (m == 2)
    {
        k = 3;
        z = 1;
    }
    return k
};

function fibmod(shw,M,Mmax){
    //alert(M+" "+Mmax);
    if(typeof M == "string") M=eval(M);
    if(isNaN(M) || M<=1 || ! isInt(M))halt('!! The modulus (the value to divide by) must be a whole number > 1')
        if(Mmax.replace(/\s/g,"")=="")Mmax=M
            else Mmax=eval(Mmax);
    if(isNaN(Mmax)||! isInt(Mmax))halt('!! The maximum modulus (the value to divide by) must be a whole number > 1');
    if(Mmax<M)halt("!! The maximum modulus must be larger then the starting modulus");
    var lens=new Array(),len;
    //if(!shw){for(var i=M;i<=Mmax;i++)putmsg(i+": "+Rpisano(i));return}
    for(var i=M;i<=Mmax;i++)
    {
        var a=1,b=1,c,len=pisano(i), cycle=[0,1,1];
        if(len>200)
        {
            putmsg("Fibs mod "+i+" cycle has length "+len);lens[lens.length]=len;continue};
            var s=(shw?"Fibs mod "+i+":":"") ;
            if(shw)
            {
                while(a!=0 || b!=1)
                {
                    c=a+b;if( c>=i )c=c-i;
                    cycle[cycle.length]=c;
                    a=b;b=c;
                };
                cycle.length-=2;len=cycle.length;
            }
        
            if(shw)putmsg(s+cycle.join(",")+" (0,1,...): length "+len)
                lens[lens.length]=len;
        }
        if(Mmax>M)putmsg("Fib cycle lengths mod "+M+".."+Mmax+":<br>"+lens.join(","))
        else if(!shw)putmsg("Fib cycle length mod "+M+" is "+len);
};