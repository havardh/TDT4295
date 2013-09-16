-- Ringbuffer testbench
library ieee;
use ieee.std_logic_1164.all;


library work;
use work.core_constants.all;

entity tb_ringbuffer is
end tb_ringbuffer;

architecture behaviour of tb_ringbuffer is
	component ringbuffer
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
	end component;

	-- Input signals:
	signal clk : std_logic := '0';
	signal sample_clk : std_logic := '0';
	signal data_in : std_logic_vector(15 downto 0) := (others => '0');
	signal address_out, address_in, roaddress : std_logic_vector(11 downto 0) := (others => '0');
	signal write_en : std_logic := '0';
	signal mode : ringbuffer_mode := NORMAL_MODE;

	-- Output signals:
	signal data_out : std_logic_vector(15 downto 0);
	signal rodata_out : std_logic_vector(15 downto 0);

	-- Clock period definitions:
	constant clk_period : time := 20 ns;			-- 50 MHz
	constant sample_clk_period : time := 45 us;	-- ~22050 Hz
begin
	-- Instantiate the unit under test:
	uut: ringbuffer port map (		-- Just use the defaults for the generics
		clk => clk,
		sample_clk => sample_clk,
		data_in => data_in,
		data_out => data_out,
		address_out => address_out,
		address_in => address_in,
		write_en => write_en,
		roaddress => roaddress,
		rodata_out => rodata_out,
		mode => mode
	);

	clk_process: process
	begin
		clk <= '0';
		wait for clk_period / 2;
		clk <= '1';
		wait for clk_period / 2;
	end process;

	sample_clk_process: process
	begin
		sample_clk <= '0';
		wait for sample_clk_period / 2;
		sample_clk <= '1';
		wait for sample_clk_period / 2;
	end process;

	stimulus_process: process
	begin
		wait for 100 ns;				-- Reset
		wait for clk_period * 10;	-- ...and even more reset

		-- Insert stuff here.
		
		wait;
	end process;
end;
