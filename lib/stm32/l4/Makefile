##
## Copyright (C) 2015 Karl Palsson <karlp@tweak.net.au>
##
## This library is free software: you can redistribute it and/or modify
## it under the terms of the GNU Lesser General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with this library.  If not, see <http://www.gnu.org/licenses/>.
##

LIBNAME		= libucmx_stm32l4
SRCLIBDIR	?= ../..

FP_FLAGS	?= -mfloat-abi=hard -mfpu=fpv4-sp-d16
PREFIX	        ?= arm-none-eabi

CC		= $(PREFIX)-gcc
AR		= $(PREFIX)-ar
TGT_CFLAGS	= -Os \
		  -Wall -Wextra -Wimplicit-function-declaration \
		  -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes \
		  -Wundef -Wshadow \
		  -I../../../include -fno-common \
		  -mcpu=cortex-m4 -mthumb $(FP_FLAGS) \
		  -Wstrict-prototypes \
		  -ffunction-sections -fdata-sections -MD -DSTM32L4
TGT_CFLAGS      += $(DEBUG_FLAGS)
ARFLAGS		= rcs

# Specific objs
OBJS		= adc.o flash.o pwr.o rcc.o

# common/shared objs
OBJS            += rcc_common_all.o
OBJS            += gpio_common_all.o gpio_common_f0234.o
OBJS            += adc_common_v2.o adc_common_v2_multi.o
OBJS            += timer_common_all.o

OBJS            += usbd.o usbd_ep0.o usbd_transfer.o
OBJS            += usbd_stm32_fsdev.o
OBJS            += usbd_msc.o

VPATH += ../:../../cm3:../common
VPATH += ../../ethernet
VPATH += ../../usbd:../../usbd/class:../../usbd/backend

include ../../Makefile.include
