#include <stddef.h>

typedef struct Result
{
    size_t buy_index;
    size_t sell_index;
} result_ty;

result_ty MaxStockProfit(const int prices[], size_t size)
{
    result_ty result = {0, 0};
    
    /* ### Write your code below this line ### */
    
	const int* p_buy = prices;
    const int* p_sell = prices + 1;
    int current_profit = 0;
    int max_profit = 0;
    
	while(p_sell - prices < size)
    {
        current_profit = *p_sell - *p_buy;
        
        if(current_profit < 0)
        {
            p_buy = p_sell;
        }
        else if(current_profit > max_profit)
        {
            max_profit = current_profit;
            result.sell_index = p_sell - prices;
            result.buy_index = p_buy - prices;
        }
        ++p_sell;
    }
	
    
    return result;
}
