/*
 * test_io.c
 *
 *  Created on: Apr 4, 2019
 *      Author: dxf7606
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <inttypes.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <sys/trace.h>		// to support TraceEvent calls
#include <sys/netmgr.h>
#include <sys/syspage.h>
#include <stdint.h>       /* for uintptr_t */
#include <hw/inout.h>     /* for in*() and out*() functions */
#include <sys/mman.h>     /* for mmap_device_io() */
#include <termios.h>

#define D_I_O_PORT_LENGTH (1)
#define A_D_BASE_ADDRESS 0x280
#define D_I_O_CONTROL_REGISTER (A_D_BASE_ADDRESS + 0x0b)
#define D_I_O_PORT_A (A_D_BASE_ADDRESS + 0x08)
#define D_I_O_PORT_B (A_D_BASE_ADDRESS + 0x09)

// make static as good programming practice (not in global symbol table)
static uintptr_t d_i_o_control_handle ;		// control register for ports A, B, and C
static uintptr_t d_i_o_port_a_handle ;
static uintptr_t d_i_o_port_b_handle ;


static void SetupDIO()
{
	d_i_o_control_handle = mmap_device_io( D_I_O_PORT_LENGTH, D_I_O_CONTROL_REGISTER ) ;
	d_i_o_port_a_handle = mmap_device_io( D_I_O_PORT_LENGTH, D_I_O_PORT_A ) ;
	d_i_o_port_b_handle = mmap_device_io( D_I_O_PORT_LENGTH, D_I_O_PORT_B ) ;
}

static void TestPorts()
{
	unsigned int testValue = 1 ;
	int count ;
	unsigned int portAvalue ;
	unsigned int portBvalue ;

	out8( d_i_o_control_handle, 0x02) ;		// make port B input

	// test output port A one bit at a time from low bit to high bit
	for ( count = 0 ; count < 8 ; count++, testValue <<= 1 )
	{
		out8( d_i_o_port_a_handle, testValue ) ;
		portBvalue = in8( d_i_o_port_b_handle ) ;
		if ( testValue != portBvalue )
			printf( "\nERROR on Port A Out to Port B In at bit %d -- got %u expected %u", count, portBvalue, testValue ) ;
	}

	out8( d_i_o_control_handle, 0x10) ;		// make port A input

	// test output port B one bit at a time from low bit to high bit
	testValue = 1 ;
	for ( count = 0 ; count < 8 ; count++, testValue <<= 1 )
	{
		out8( d_i_o_port_b_handle, testValue ) ;
		portAvalue = in8( d_i_o_port_a_handle ) ;
		if ( testValue != portAvalue )
			printf( "\nERROR on Port B Out to Port A In at bit %d -- got %u expected %u", count, portAvalue, testValue ) ;
	}
	printf( "\nDigital I O ports A and B testing completed\n" ) ;
}

int GetRootAccess()
{
	int status = 0 ;
	int privity_err ;

	/* Give this thread root permissions to access the hardware */
	privity_err = ThreadCtl( _NTO_TCTL_IO, NULL );
	if ( privity_err == -1 )
	{
		printf("\nCan't get root permissions");
		fprintf( stderr, "can't get root permissions\n" );
		status = -1;
	}

	return status ;
}

int main(int argc, char *argv[])
{
	if ( ! GetRootAccess() )
	{
		SetupDIO() ;
		TestPorts();
	}
	else
		printf( "\nFailure getting root access for I/O register mapping\n") ;

	return EXIT_SUCCESS;
}

