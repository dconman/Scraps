//gcc 5.4.0

#include <wchar.h>

#define MAX 500

wchar_t codes[][2] = {
    {119808,119834},
    {119860,119886},
    {119912,119938},
    {120224,120250},
    {120276,120302},
    {120328,120354},
    {120380,120406},
    {119964,119990},
    {120016,120042},
    {120068,120094},
    {120172,120198},
    {120432,120458},
    {120120,120146},
    {9398,9424},
    {127248,9372},
    {127280,127280},
    {127312,127312},
    {127344,127344}
};

int main(void)
{
    wint_t in = 0;
    
    size_t numCodes = sizeof(codes)/sizeof(codes[0]);
    wchar_t out[numCodes][MAX];
    
    for(int i = 0; in != WEOF && i < MAX-1; i++)
    {
        in = getwchar();
        
        wchar_t wv = 0;
        int type = 2;
        if(in == WEOF) wv = 0;
        else if((wv = in - 65) < 26) type = 0;
        else if((wv = in - 97) < 26) type = 1;
        else wv = in;
        
        for(int j = 0; j < numCodes; j++)
            out[j][i] = wv + (type > 1 ? 0 : codes[j][type]);
    
    }
    
    for(int j = 0; j < numCodes; j++)
        for(int i = 0;i < MAX-1; i++)
        {
            putwchar(out[j][i] ? out[j][i] : L'\n');
            if(!out[j][i])
                break;
        }
    
    
    return 0;
}
