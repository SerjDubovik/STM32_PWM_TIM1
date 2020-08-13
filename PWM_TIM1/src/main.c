
#include "stm32f10x.h"


//#define PWM_VALUE           40
#define TMR_T               360		// 100 kHz
//#define DEADTIME            20

#define PP_MODE
//#define COMPL_MODE


unsigned int PWM_VALUE = 40;
unsigned int DEADTIME = 20;


int main(void)
{
	    RCC->APB2ENR|= RCC_APB2ENR_IOPAEN;
	    RCC->APB2ENR|= RCC_APB2ENR_IOPBEN;
		RCC->APB2ENR|= RCC_APB2ENR_IOPCEN;

	    RCC->APB2ENR|= RCC_APB2ENR_TIM1EN;


		//���������������� GPIOC.13	������� ������ �� �����
		GPIOC->CRH &= ~GPIO_CRH_MODE13;   			// �������� ������� MODE
		GPIOC->CRH &= ~GPIO_CRH_CNF13;    			// �������� ������� CNF
		GPIOC->CRH |=  GPIO_CRH_MODE13;   			// �����, 50MHz
		GPIOC->CRH &= ~GPIO_CRH_CNF13;    			// ������ ����������, ������������


		GPIOA->CRH &= ~GPIO_CRH_MODE8;   			// �������� ������� MODE
		GPIOA->CRH &= ~GPIO_CRH_CNF8;    			// �������� ������� CNF
		GPIOA->CRH |=  GPIO_CRH_MODE8;   			// �����, 50MHz
		GPIOA->CRH |=  GPIO_CRH_MODE8 | GPIO_CRH_CNF8_1;  // ����������� ����� � ���������� �-��, 50MHz


		GPIOA->CRH &= ~GPIO_CRH_MODE9;   			// �������� ������� MODE
		GPIOA->CRH &= ~GPIO_CRH_CNF9;    			// �������� ������� CNF
		GPIOA->CRH |=  GPIO_CRH_MODE9;   			// �����, 50MHz
		GPIOA->CRH |=  GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1;  // ����������� ����� � ���������� �-��, 50MHz



	#ifdef PP_MODE
	    //CH1: PWM mode 2, CH2: PWM mode 1, preload enabled on all channels
	    TIM1->CCMR1=TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;
	    TIM1->CCER=TIM_CCER_CC1E | TIM_CCER_CC2E;
	    TIM1->BDTR=TIM_BDTR_MOE;
	    TIM1->CCR1=TMR_T - PWM_VALUE;
	    TIM1->CCR2=PWM_VALUE;
	    TIM1->ARR=TMR_T;
	    TIM1->CR1=TIM_CR1_ARPE | TIM_CR1_CMS_1 | TIM_CR1_CMS_0;
	    TIM1->CR1|=TIM_CR1_CEN;
	    TIM1->EGR=TIM_EGR_UG;
	#endif

	#ifdef COMPL_MODE
	    //CH1: PWM mode with complementary output & deadtime
	    TIM1->CCMR1=TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE;
	    TIM1->CCER=TIM_CCER_CC1E | TIM_CCER_CC1NE;
	    TIM1->BDTR=TIM_BDTR_MOE | DEADTIME;
	    TIM1->CCR1=PWM_VALUE;
	    TIM1->ARR=TMR_T;
	    TIM1->CR1=TIM_CR1_ARPE;
	    TIM1->CR1|=TIM_CR1_CEN;
	    TIM1->EGR=TIM_EGR_UG;
	#endif



	for(;;)
	{
	    TIM1->CCR1=TMR_T - PWM_VALUE;
	    TIM1->CCR2=PWM_VALUE;
	}// ������ ������������ �����
}// ������ �����
