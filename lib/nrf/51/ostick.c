/** @addtogroup ostick_defines
 *
 * @brief <b>Access functions for the NRF51 Clock Controller </b>
 * @ingroup NRF51_defines
 * LGPL License Terms @ref lgpl_license
 * @author @htmlonly &copy; @endhtmlonly 2016
 * Roel Postelmans <postelmansroel@gmail.com>
 *
 */

/*
 * This file is part of the unicore-mx project.
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

#include <unicore-mx/nrf/ostick.h>
#include <unicore-mx/nrf/rtc.h>
#include <unicore-mx/nrf/clock.h>
#include <unicore-mx/nrf/periph.h>

#define OSTICK_PRESCALE_MS_SHIFT  5
#ifdef OSTICK_USE_RTC0
#define OSTICK_TIMER RTC0
#elif defined(OSTICK_USE_RTC1)
#define OSTICK_TIMER RTC1
#elif defined(OSTICK_USE_RTC2)
#define OSTICK_TIMER RTC2
#else
#define OSTICK_TIMER RTC0
#endif

/** @brief Initialize the ostick
 *
 * @param[in] interval_ms: The interval of the ostick in ms
 */
void ostick_init(uint16_t interval_ms)
{
    clock_start_lfclk(1);
    rtc_set_prescaler(OSTICK_TIMER, interval_ms<<OSTICK_PRESCALE_MS_SHIFT);
}

/** @brief Start the ostick */
void ostick_start()
{
    periph_enable_irq(OSTICK_TIMER);
    rtc_enable_interrupt(OSTICK_TIMER, RTC_INTEN_TICK);
    rtc_start(OSTICK_TIMER);
}

/** @brief Ostick interupt routine */
void ostick_isr()
{
    rtc_clear(OSTICK_TIMER);
}

/** @brief Stop the ostick */
void ostick_stop()
{
    periph_disable_irq(OSTICK_TIMER);
    rtc_disable_interrupt(OSTICK_TIMER, RTC_INTEN_TICK);
    rtc_stop(OSTICK_TIMER);
}
