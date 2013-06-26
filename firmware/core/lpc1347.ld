ENTRY(Reset_Handler)

MEMORY
{
	sram	:	ORIGIN = 0x10000000, LENGTH = 8k
	flash	:	ORIGIN = 0x00000000, LENGTH = 64k
}

_end_stack = 0x10001FF0;

SECTIONS {
	. = ORIGIN(flash);

	vectors :
	{
		*(.vectors)
	} >flash

	.text :
	{
		*(.text)
		*(.rodata)
		*(.rodata*)
		_end_text = .;
	} >flash
	
	.preinit_array     :
	{
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array*))
		PROVIDE_HIDDEN (__preinit_array_end = .);
	} >flash
	.init_array :
	{
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array*))
		PROVIDE_HIDDEN (__init_array_end = .);
	} >flash
	.fini_array :
	{
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(.fini_array*))
		KEEP (*(SORT(.fini_array.*)))
		PROVIDE_HIDDEN (__fini_array_end = .);
	} >flash

	.data : 
	{
		_start_data = .;
		*(.data)
		_end_data = .;
	} >sram AT >flash

	.bss :
	{
		__bss_start__ = .;
		_start_bss = .;
		*(.bss)
		_end_bss = .;
		__bss_end__ = .;
	} >sram

	. = ALIGN(4);
	
	_start_stack = .;
}

_end = .;
PROVIDE(end = .);

