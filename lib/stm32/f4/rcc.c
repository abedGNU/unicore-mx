/** @defgroup rcc_file RCC
 *
 * @ingroup STM32F4xx
 *
 * @section rcc_f4_api_ex Reset and Clock Control API.
 *
 * @brief <b>unicore-mx STM32F4xx Reset and Clock Control</b>
 *
 * @author @htmlonly &copy; @endhtmlonly 2013 Frantisek Burian <BuFran at seznam.cz>
 *
 * @date 18 Jun 2013
 *
 * This library supports the Reset and Clock Control System in the STM32 series
 * of ARM Cortex Microcontrollers by ST Microelectronics.
 *
 * LGPL License Terms @ref lgpl_license
 */

/*
 * Copyright (C) 2009 Federico Ruiz-Ugalde <memeruiz at gmail dot com>
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 * Copyright (C) 2010 Thomas Otto <tommi@viadmin.org>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <unicore-mx/cm3/assert.h>
#include <unicore-mx/stm32/rcc.h>
#include <unicore-mx/stm32/pwr.h>
#include <unicore-mx/stm32/flash.h>

/**@{*/

/* Set the default clock frequencies after reset. */
uint32_t rcc_ahb_frequency = 16000000;
uint32_t rcc_apb1_frequency = 16000000;
uint32_t rcc_apb2_frequency = 16000000;

const struct rcc_clock_scale rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_END] = {
	{ /* 48MHz */
		.pllm = 8,
		.plln = 96,
		.pllp = 2,
		.pllq = 2,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_4,
		.ppre2 = RCC_CFGR_PPRE_DIV_2,
		.power_save = 1,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_3WS,
		.ahb_frequency  = 48000000,
		.apb1_frequency = 12000000,
		.apb2_frequency = 24000000,
	},
	{ /* 84MHz */
		.pllm = 8,
		.plln = 336,
		.pllp = 4,
		.pllq = 7,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_2,
		.ppre2 = RCC_CFGR_PPRE_DIV_NONE,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_2WS,
		.ahb_frequency  = 84000000,
		.apb1_frequency = 42000000,
		.apb2_frequency = 84000000,
	},
	{ /* 100MHz */
		.pllm = 8,
		.plln = 192,
		.pllp = 2,
		.pllq = 4,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_2,
		.ppre2 = RCC_CFGR_PPRE_DIV_NONE,
		.power_save = 1,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_2WS,
		.ahb_frequency  = 100000000,
		.apb1_frequency = 50000000,
		.apb2_frequency = 100000000,
	},
	{ /* 120MHz */
		.pllm = 8,
		.plln = 240,
		.pllp = 2,
		.pllq = 5,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_4,
		.ppre2 = RCC_CFGR_PPRE_DIV_2,
		.power_save = 1,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_3WS,
		.ahb_frequency  = 120000000,
		.apb1_frequency = 30000000,
		.apb2_frequency = 60000000,
	},
	{ /* 168MHz */
		.pllm = 8,
		.plln = 336,
		.pllp = 2,
		.pllq = 7,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_4,
		.ppre2 = RCC_CFGR_PPRE_DIV_2,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_5WS,
		.ahb_frequency  = 168000000,
		.apb1_frequency = 42000000,
		.apb2_frequency = 84000000,
	},
};

const struct rcc_clock_scale rcc_hse_12mhz_3v3[RCC_CLOCK_3V3_END] = {
	{ /* 48MHz */
		.pllm = 12,
		.plln = 96,
		.pllp = 2,
		.pllq = 2,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_4,
		.ppre2 = RCC_CFGR_PPRE_DIV_2,
		.power_save = 1,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_3WS,
		.ahb_frequency  = 48000000,
		.apb1_frequency = 12000000,
		.apb2_frequency = 24000000,
	},
	{ /* 84MHz */
		.pllm = 12,
		.plln = 336,
		.pllp = 4,
		.pllq = 7,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_2,
		.ppre2 = RCC_CFGR_PPRE_DIV_NONE,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_2WS,
		.ahb_frequency  = 84000000,
		.apb1_frequency = 42000000,
		.apb2_frequency = 84000000,
	},
	{ /* 100MHz */
		.pllm = 12,
		.plln = 192,
		.pllp = 2,
		.pllq = 4,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_2,
		.ppre2 = RCC_CFGR_PPRE_DIV_NONE,
		.power_save = 1,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_2WS,
		.ahb_frequency  = 100000000,
		.apb1_frequency = 50000000,
		.apb2_frequency = 100000000,
	},
	{ /* 120MHz */
		.pllm = 12,
		.plln = 240,
		.pllp = 2,
		.pllq = 5,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_4,
		.ppre2 = RCC_CFGR_PPRE_DIV_2,
		.power_save = 1,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_3WS,
		.ahb_frequency  = 120000000,
		.apb1_frequency = 30000000,
		.apb2_frequency = 60000000,
	},
	{ /* 168MHz */
		.pllm = 12,
		.plln = 336,
		.pllp = 2,
		.pllq = 7,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_4,
		.ppre2 = RCC_CFGR_PPRE_DIV_2,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_5WS,
		.ahb_frequency  = 168000000,
		.apb1_frequency = 42000000,
		.apb2_frequency = 84000000,
	},
};

const struct rcc_clock_scale rcc_hse_16mhz_3v3[RCC_CLOCK_3V3_END] = {
	{ /* 48MHz */
		.pllm = 16,
		.plln = 96,
		.pllp = 2,
		.pllq = 2,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_4,
		.ppre2 = RCC_CFGR_PPRE_DIV_2,
		.power_save = 1,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_3WS,
		.ahb_frequency  = 48000000,
		.apb1_frequency = 12000000,
		.apb2_frequency = 24000000,
	},
	{ /* 84MHz */
		.pllm = 16,
		.plln = 336,
		.pllp = 4,
		.pllq = 7,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_2,
		.ppre2 = RCC_CFGR_PPRE_DIV_NONE,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_2WS,
		.ahb_frequency  = 84000000,
		.apb1_frequency = 42000000,
		.apb2_frequency = 84000000,
	},
	{ /* 100MHz */
		.pllm = 16,
		.plln = 192,
		.pllp = 2,
		.pllq = 4,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_2,
		.ppre2 = RCC_CFGR_PPRE_DIV_NONE,
		.power_save = 1,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_2WS,
		.ahb_frequency  = 100000000,
		.apb1_frequency = 50000000,
		.apb2_frequency = 100000000,
	},
	{ /* 120MHz */
		.pllm = 16,
		.plln = 240,
		.pllp = 2,
		.pllq = 5,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_4,
		.ppre2 = RCC_CFGR_PPRE_DIV_2,
		.power_save = 1,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_3WS,
		.ahb_frequency  = 120000000,
		.apb1_frequency = 30000000,
		.apb2_frequency = 60000000,
	},
	{ /* 168MHz */
		.pllm = 16,
		.plln = 336,
		.pllp = 2,
		.pllq = 7,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_4,
		.ppre2 = RCC_CFGR_PPRE_DIV_2,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_5WS,
		.ahb_frequency  = 168000000,
		.apb1_frequency = 42000000,
		.apb2_frequency = 84000000,
	},
};

const struct rcc_clock_scale rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_END] = {
	{ /* 48MHz */
		.pllm = 25,
		.plln = 96,
		.pllp = 2,
		.pllq = 2,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_4,
		.ppre2 = RCC_CFGR_PPRE_DIV_2,
		.power_save = 1,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_3WS,
		.ahb_frequency  = 48000000,
		.apb1_frequency = 12000000,
		.apb2_frequency = 24000000,
	},
	{ /* 84MHz */
		.pllm = 25,
		.plln = 336,
		.pllp = 4,
		.pllq = 7,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_2,
		.ppre2 = RCC_CFGR_PPRE_DIV_NONE,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_2WS,
		.ahb_frequency  = 84000000,
		.apb1_frequency = 42000000,
		.apb2_frequency = 84000000,
	},
	{ /* 100MHz */
		.pllm = 25,
		.plln = 192,
		.pllp = 2,
		.pllq = 4,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_2,
		.ppre2 = RCC_CFGR_PPRE_DIV_NONE,
		.power_save = 1,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_2WS,
		.ahb_frequency  = 100000000,
		.apb1_frequency = 50000000,
		.apb2_frequency = 100000000,
	},
	{ /* 120MHz */
		.pllm = 25,
		.plln = 240,
		.pllp = 2,
		.pllq = 5,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_4,
		.ppre2 = RCC_CFGR_PPRE_DIV_2,
		.power_save = 1,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_3WS,
		.ahb_frequency  = 120000000,
		.apb1_frequency = 30000000,
		.apb2_frequency = 60000000,
	},
	{ /* 168MHz */
		.pllm = 25,
		.plln = 336,
		.pllp = 2,
		.pllq = 7,
		.pllr = 0,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_4,
		.ppre2 = RCC_CFGR_PPRE_DIV_2,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
				FLASH_ACR_LATENCY_5WS,
		.ahb_frequency  = 168000000,
		.apb1_frequency = 42000000,
		.apb2_frequency = 84000000,
	},
};

void rcc_osc_ready_int_clear(enum rcc_osc osc)
{
	switch (osc) {
	case RCC_PLL:
		RCC_CIR |= RCC_CIR_PLLRDYC;
		break;
	case RCC_HSE:
		RCC_CIR |= RCC_CIR_HSERDYC;
		break;
	case RCC_HSI:
		RCC_CIR |= RCC_CIR_HSIRDYC;
		break;
	case RCC_LSE:
		RCC_CIR |= RCC_CIR_LSERDYC;
		break;
	case RCC_LSI:
		RCC_CIR |= RCC_CIR_LSIRDYC;
		break;
	case RCC_PLLSAI:
		RCC_CIR |= RCC_CIR_PLLSAIRDYC;
		break;
	case RCC_PLLI2S:
		RCC_CIR |= RCC_CIR_PLLI2SRDYC;
		break;
	}
}

void rcc_osc_ready_int_enable(enum rcc_osc osc)
{
	switch (osc) {
	case RCC_PLL:
		RCC_CIR |= RCC_CIR_PLLRDYIE;
		break;
	case RCC_HSE:
		RCC_CIR |= RCC_CIR_HSERDYIE;
		break;
	case RCC_HSI:
		RCC_CIR |= RCC_CIR_HSIRDYIE;
		break;
	case RCC_LSE:
		RCC_CIR |= RCC_CIR_LSERDYIE;
		break;
	case RCC_LSI:
		RCC_CIR |= RCC_CIR_LSIRDYIE;
		break;
	case RCC_PLLSAI:
		RCC_CIR |= RCC_CIR_PLLSAIRDYIE;
		break;
	case RCC_PLLI2S:
		RCC_CIR |= RCC_CIR_PLLI2SRDYIE;
		break;
	}
}

void rcc_osc_ready_int_disable(enum rcc_osc osc)
{
	switch (osc) {
	case RCC_PLL:
		RCC_CIR &= ~RCC_CIR_PLLRDYIE;
		break;
	case RCC_HSE:
		RCC_CIR &= ~RCC_CIR_HSERDYIE;
		break;
	case RCC_HSI:
		RCC_CIR &= ~RCC_CIR_HSIRDYIE;
		break;
	case RCC_LSE:
		RCC_CIR &= ~RCC_CIR_LSERDYIE;
		break;
	case RCC_LSI:
		RCC_CIR &= ~RCC_CIR_LSIRDYIE;
		break;
	case RCC_PLLSAI:
		RCC_CIR &= ~RCC_CIR_PLLSAIRDYIE;
		break;
	case RCC_PLLI2S:
		RCC_CIR &= ~RCC_CIR_PLLI2SRDYIE;
		break;
	}
}

int rcc_osc_ready_int_flag(enum rcc_osc osc)
{
	switch (osc) {
	case RCC_PLL:
		return ((RCC_CIR & RCC_CIR_PLLRDYF) != 0);
	case RCC_HSE:
		return ((RCC_CIR & RCC_CIR_HSERDYF) != 0);
	case RCC_HSI:
		return ((RCC_CIR & RCC_CIR_HSIRDYF) != 0);
	case RCC_LSE:
		return ((RCC_CIR & RCC_CIR_LSERDYF) != 0);
	case RCC_LSI:
		return ((RCC_CIR & RCC_CIR_LSIRDYF) != 0);
	case RCC_PLLSAI:
		return ((RCC_CIR & RCC_CIR_PLLSAIRDYF) != 0);
	case RCC_PLLI2S:
		return ((RCC_CIR & RCC_CIR_PLLI2SRDYF) != 0);
	}
	return 0;
}

void rcc_css_int_clear(void)
{
	RCC_CIR |= RCC_CIR_CSSC;
}

int rcc_css_int_flag(void)
{
	return ((RCC_CIR & RCC_CIR_CSSF) != 0);
}

void rcc_wait_for_osc_ready(enum rcc_osc osc)
{
	switch (osc) {
	case RCC_PLL:
		while ((RCC_CR & RCC_CR_PLLRDY) == 0);
		break;
	case RCC_HSE:
		while ((RCC_CR & RCC_CR_HSERDY) == 0);
		break;
	case RCC_HSI:
		while ((RCC_CR & RCC_CR_HSIRDY) == 0);
		break;
	case RCC_LSE:
		while ((RCC_BDCR & RCC_BDCR_LSERDY) == 0);
		break;
	case RCC_LSI:
		while ((RCC_CSR & RCC_CSR_LSIRDY) == 0);
		break;
	case RCC_PLLSAI:
		while ((RCC_CR & RCC_CR_PLLSAIRDY) == 0);
		break;
	case RCC_PLLI2S:
		while ((RCC_CR & RCC_CR_PLLI2SRDY) == 0);
		break;
	}
}

void rcc_wait_for_sysclk_status(enum rcc_osc osc)
{
	switch (osc) {
	case RCC_PLL:
		while ((RCC_CFGR & ((1 << 1) | (1 << 0))) != RCC_CFGR_SWS_PLL);
		break;
	case RCC_HSE:
		while ((RCC_CFGR & ((1 << 1) | (1 << 0))) != RCC_CFGR_SWS_HSE);
		break;
	case RCC_HSI:
		while ((RCC_CFGR & ((1 << 1) | (1 << 0))) != RCC_CFGR_SWS_HSI);
		break;
	default:
		/* Shouldn't be reached. */
		break;
	}
}

void rcc_osc_on(enum rcc_osc osc)
{
	switch (osc) {
	case RCC_PLL:
		RCC_CR |= RCC_CR_PLLON;
		break;
	case RCC_HSE:
		RCC_CR |= RCC_CR_HSEON;
		break;
	case RCC_HSI:
		RCC_CR |= RCC_CR_HSION;
		break;
	case RCC_LSE:
		RCC_BDCR |= RCC_BDCR_LSEON;
		break;
	case RCC_LSI:
		RCC_CSR |= RCC_CSR_LSION;
		break;
	case RCC_PLLSAI:
		RCC_CR |= RCC_CR_PLLSAION;
		break;
	case RCC_PLLI2S:
		RCC_CR |= RCC_CR_PLLI2SON;
		break;
	}
}

void rcc_osc_off(enum rcc_osc osc)
{
	switch (osc) {
	case RCC_PLL:
		RCC_CR &= ~RCC_CR_PLLON;
		break;
	case RCC_HSE:
		RCC_CR &= ~RCC_CR_HSEON;
		break;
	case RCC_HSI:
		RCC_CR &= ~RCC_CR_HSION;
		break;
	case RCC_LSE:
		RCC_BDCR &= ~RCC_BDCR_LSEON;
		break;
	case RCC_LSI:
		RCC_CSR &= ~RCC_CSR_LSION;
		break;
	case RCC_PLLSAI:
		RCC_CR &= ~RCC_CR_PLLSAION;
		break;
	case RCC_PLLI2S:
		RCC_CR &= ~RCC_CR_PLLI2SON;
		break;
	}
}

void rcc_css_enable(void)
{
	RCC_CR |= RCC_CR_CSSON;
}

void rcc_css_disable(void)
{
	RCC_CR &= ~RCC_CR_CSSON;
}

void rcc_osc_bypass_enable(enum rcc_osc osc)
{
	switch (osc) {
	case RCC_HSE:
		RCC_CR |= RCC_CR_HSEBYP;
		break;
	case RCC_LSE:
		RCC_BDCR |= RCC_BDCR_LSEBYP;
		break;
	case RCC_PLL:
	case RCC_HSI:
	case RCC_LSI:
	default:
		/* Do nothing, only HSE/LSE allowed here. */
		break;
	}
}

void rcc_osc_bypass_disable(enum rcc_osc osc)
{
	switch (osc) {
	case RCC_HSE:
		RCC_CR &= ~RCC_CR_HSEBYP;
		break;
	case RCC_LSE:
		RCC_BDCR &= ~RCC_BDCR_LSEBYP;
		break;
	case RCC_PLL:
	case RCC_HSI:
	case RCC_LSI:
	default:
		/* Do nothing, only HSE/LSE allowed here. */
		break;
	}
}

void rcc_set_sysclk_source(uint32_t clk)
{
	uint32_t reg32;

	reg32 = RCC_CFGR;
	reg32 &= ~((1 << 1) | (1 << 0));
	RCC_CFGR = (reg32 | clk);
}

void rcc_set_pll_source(uint32_t pllsrc)
{
	uint32_t reg32;

	reg32 = RCC_PLLCFGR;
	reg32 &= ~(1 << 22);
	RCC_PLLCFGR = (reg32 | (pllsrc << 22));
}

void rcc_set_ppre2(uint32_t ppre2)
{
	uint32_t reg32;

	reg32 = RCC_CFGR;
	reg32 &= ~((1 << 13) | (1 << 14) | (1 << 15));
	RCC_CFGR = (reg32 | (ppre2 << 13));
}

void rcc_set_ppre1(uint32_t ppre1)
{
	uint32_t reg32;

	reg32 = RCC_CFGR;
	reg32 &= ~((1 << 10) | (1 << 11) | (1 << 12));
	RCC_CFGR = (reg32 | (ppre1 << 10));
}

void rcc_set_hpre(uint32_t hpre)
{
	uint32_t reg32;

	reg32 = RCC_CFGR;
	reg32 &= ~((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7));
	RCC_CFGR = (reg32 | (hpre << 4));
}

void rcc_set_rtcpre(uint32_t rtcpre)
{
	uint32_t reg32;

	reg32 = RCC_CFGR;
	reg32 &= ~((1 << 16) | (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20));
	RCC_CFGR = (reg32 | (rtcpre << 16));
}

void rcc_set_main_pll_hsi(uint32_t pllm, uint32_t plln, uint32_t pllp,
			  uint32_t pllq, uint32_t pllr)
{
	uint32_t reg32 = RCC_PLLCFGR;
	uint8_t		new_r;

	/* If passed in value is legal, use it, else use version from register */
	new_r = (pllr > 1) ? pllr :
					     (reg32 >> RCC_PLLCFGR_PLLR_SHIFT) & RCC_PLLCFGR_PLLR_MASK;

	/* mask out any previous values */
	reg32 &= ~(
		 RCC_PLLCFGR_PLLSRC |	/* 0 = HSI */
		(RCC_PLLCFGR_PLLM_MASK << RCC_PLLCFGR_PLLM_SHIFT) |
		(RCC_PLLCFGR_PLLN_MASK << RCC_PLLCFGR_PLLN_SHIFT) |
		(RCC_PLLCFGR_PLLP_MASK << RCC_PLLCFGR_PLLP_SHIFT) |
		(RCC_PLLCFGR_PLLQ_MASK << RCC_PLLCFGR_PLLQ_SHIFT) |
		(RCC_PLLCFGR_PLLR_MASK << RCC_PLLCFGR_PLLR_SHIFT));
		
	/* add back new values, PLLSRC is HSI */
	RCC_PLLCFGR = reg32 | (
		(pllm << RCC_PLLCFGR_PLLM_SHIFT) |
		(plln << RCC_PLLCFGR_PLLN_SHIFT) |
		(((pllp >> 1) - 1) << RCC_PLLCFGR_PLLP_SHIFT) |
		(pllq << RCC_PLLCFGR_PLLQ_SHIFT) |
		(new_r << RCC_PLLCFGR_PLLR_SHIFT));
}

/* Note it adjusts PLLP */
void rcc_set_main_pll_hse(uint32_t pllm, uint32_t plln, uint32_t pllp,
			  uint32_t pllq, uint32_t pllr)
{
	uint32_t reg32 = RCC_PLLCFGR;
	uint8_t		new_r;

	/* If passed in value is legal, use it, else use version from register */
	new_r = (pllr > 1) ? pllr :
						 (reg32 >> RCC_PLLCFGR_PLLR_SHIFT) & RCC_PLLCFGR_PLLR_MASK;

	/* mask out any previous values */
	reg32 &= ~(
		(RCC_PLLCFGR_PLLM_MASK << RCC_PLLCFGR_PLLM_SHIFT) |
		(RCC_PLLCFGR_PLLN_MASK << RCC_PLLCFGR_PLLN_SHIFT) |
		(RCC_PLLCFGR_PLLP_MASK << RCC_PLLCFGR_PLLP_SHIFT) |
		(RCC_PLLCFGR_PLLQ_MASK << RCC_PLLCFGR_PLLQ_SHIFT) |
		(RCC_PLLCFGR_PLLR_MASK << RCC_PLLCFGR_PLLR_SHIFT));
		
	/* add in the new values + PLLSRC */
	RCC_PLLCFGR = reg32 | RCC_PLLCFGR_PLLSRC | (
		(pllm << RCC_PLLCFGR_PLLM_SHIFT) |
		(plln << RCC_PLLCFGR_PLLN_SHIFT) |
		(((pllp >> 1) - 1) << RCC_PLLCFGR_PLLP_SHIFT) |
		(pllq << RCC_PLLCFGR_PLLQ_SHIFT) |
		(new_r << RCC_PLLCFGR_PLLR_SHIFT));
}

uint32_t rcc_system_clock_source(void)
{
	/* Return the clock source which is used as system clock. */
	return (RCC_CFGR & 0x000c) >> 2;
}

void rcc_clock_setup_hse_3v3(const struct rcc_clock_scale *clock)
{
	/* Enable internal high-speed oscillator. */
	rcc_osc_on(RCC_HSI);
	rcc_wait_for_osc_ready(RCC_HSI);

	/* Select HSI as SYSCLK source. */
	rcc_set_sysclk_source(RCC_CFGR_SW_HSI);

	/* Enable external high-speed oscillator 8MHz. */
	rcc_osc_on(RCC_HSE);
	rcc_wait_for_osc_ready(RCC_HSE);

	/* Enable/disable high performance mode */
	if (!clock->power_save) {
		pwr_set_vos_scale(PWR_SCALE1);
	} else {
		pwr_set_vos_scale(PWR_SCALE2);
	}

	/*
	 * Set prescalers for AHB, ADC, ABP1, ABP2.
	 * Do this before touching the PLL (TODO: why?).
	 */
	rcc_set_hpre(clock->hpre);
	rcc_set_ppre1(clock->ppre1);
	rcc_set_ppre2(clock->ppre2);

	rcc_set_main_pll_hse(clock->pllm, clock->plln,
			clock->pllp, clock->pllq, clock->pllr);

	/* Enable PLL oscillator and wait for it to stabilize. */
	rcc_osc_on(RCC_PLL);
	rcc_wait_for_osc_ready(RCC_PLL);

	/* Configure flash settings. */
	flash_set_ws(clock->flash_config);

	/* Select PLL as SYSCLK source. */
	rcc_set_sysclk_source(RCC_CFGR_SW_PLL);

	/* Wait for PLL clock to be selected. */
	rcc_wait_for_sysclk_status(RCC_PLL);

	/* Set the peripheral clock frequencies used. */
	rcc_ahb_frequency  = clock->ahb_frequency;
	rcc_apb1_frequency = clock->apb1_frequency;
	rcc_apb2_frequency = clock->apb2_frequency;

	/* Disable internal high-speed oscillator. */
	rcc_osc_off(RCC_HSI);
}

/**@}*/
