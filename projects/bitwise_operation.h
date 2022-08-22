#define set_bit(register,bit) register |=(1<< bit)
#define clear_bit(register,bit) register &=~(1<< bit)
#define get_bit(register,bit) bit=register&(1<< bit)
#define toggle_bit(register,bit) register ^=(1<< bit)