#include "coins_available.h"

Coins_available::Coins_available() {

    BITCOIN = new Coin("bitcoin","https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd");
    ETHEREUM = new Coin("ethereum","https://api.coingecko.com/api/v3/simple/price?ids=ethereum&vs_currencies=usd");
    TETHER = new Coin("tether","https://api.coingecko.com/api/v3/simple/price?ids=tether&vs_currencies=usd");
    BNB = new Coin("binancecoin","https://api.coingecko.com/api/v3/simple/price?ids=binancecoin&vs_currencies=usd");
    SOLANA = new Coin("solana","https://api.coingecko.com/api/v3/simple/price?ids=solana&vs_currencies=usd");
    XRP = new Coin("ripple","https://api.coingecko.com/api/v3/simple/price?ids=ripple&vs_currencies=usd");
    TRON = new Coin("tron","https://api.coingecko.com/api/v3/simple/price?ids=tron&vs_currencies=usd");

}
void Coins_available :: update_all(){
    BITCOIN->Update();
}
