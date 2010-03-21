/*
 * Copyright (C) INSA Toulouse
 * Author: Sebastien DI MERCURIO
 *
 * This file is part of brushless DC motor controller.
 *
 * Brushless DC motor controller is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * Brushless DC motor controller is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public
 * License along with Brushless DC motor controller; see the file COPYING.  If not,
 * write to the Free Software Foundation, Inc., 51 Franklin Street,
 * Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "interface.h"
#include "interface_uart.h"

void Init_Interface(void)
{
#if (_INTERFACE_TYPE_ == _INTERFACE_UART_)
	Init_Interface_uart();
#else
#endif /* _INTERFACE_TYPE_ */
}

void Interface(void)
{
#if (_INTERFACE_TYPE_ == _INTERFACE_UART_)
	Interface_uart();
#else
#endif /* _INTERFACE_TYPE_ */
}