-- Ring buffer / input buffer / output buffer module
-- The ring buffer is a configurable buffer that can operate in both ring buffer
-- and normal memory mode.
library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.all; -- for typecasts

library work;
use work.core_constants.all;

entity ringbuffer is
	generic(
		data_width		: natural := 16;		-- Width of a buffer word
		address_width	: natural := 12;		-- Width of the address inputs
		buffer_size		: natural := 4096;	-- Size of the buffer, in words
		window_size		: natural := 2048		-- Size of the ring buffer window, in words
	);
	port(
		clk 			: in std_logic; -- Main clock ("small cycle" clock)
		sample_clk	: in std_logic; -- Sample clock ("large cycle" clock)

		-- Data and address I/O for using the buffer as output buffer:
		data_in		: in std_logic_vector(data_width - 1 downto 0);			-- Data input
		data_out		: out std_logic_vector(data_width - 1 downto 0);		-- Data output
		address_out : in std_logic_vector(address_width - 1 downto 0);		-- Address for output data
		address_in	: in std_logic_vector(address_width - 1 downto 0);		-- Address for input data
		write_en		: in std_logic;			-- Write enable for writing data from data_in to address address_in

		-- Data and address I/O for using the buffer as input buffer:
		rodata_out	: out std_logic_vector(data_width - 1 downto 0);		-- Read-only data output
		roaddress	: in std_logic_vector(address_width - 1 downto 0);		-- Address for the read-only data output

		mode			: in ringbuffer_mode	-- Buffer mode
	);
end ringbuffer;

architecture behaviour of ringbuffer is
	subtype buffer_word is std_logic_vector(data_width - 1 downto 0);
	type buffer_memory_array is array (0 to buffer_size) of buffer_word;

	signal rw_window_base : std_logic_vector(address_width - 1 downto 0) := (others => '0');
	signal ro_window_base : std_logic_vector(address_width - 1 downto 0) := (others => '0');
	signal memory_array : buffer_memory_array;
begin
	update_process: process(write_en, memory_array)
	begin
		if rising_edge(write_en) then
			memory_array(to_integer(unsigned(address_in) + unsigned(rw_window_base))) <= data_in;
		end if;
	end process update_process;

	-- TODO: support updating window pointers and switching modes.

	rodata_out <= memory_array(to_integer(unsigned(roaddress) + unsigned(ro_window_base)));
	data_out <= memory_array(to_integer(unsigned(address_out) + unsigned(rw_window_base)));
end behaviour;
