-- Pipeline module

library ieee;
use ieee.std_logic_1164.ALL;

library work;
use work.core_constants.all;

entity pipeline is
	generic (
		address_width	: natural := 28;
		data_width		: natural := 16;
		num_cores		: natural := 4
	);

	port (
		clk			: in std_logic;			-- Small cycle clock
		sample_clk	: in std_logic;	-- Large cucle clock

		-- Connections to the EBI bus interface:
		address	: in std_logic_vector(address_width - 1 downto 0);
		data		: in std_logic_vector(data_width - 1 downto 0);
		write_en	: in std_logic
	);
end entity;

architecture behaviour of pipeline is
	-- Components
	
	component ringbuffer is
		generic(
			data_width		: natural := 16;		-- Width of a buffer word
			address_width	: natural := 12;		-- Width of the address inputs
			buffer_size		: natural := 4096;	-- Size of the buffer, in words
			window_size		: natural := 2048		-- Size of the ring buffer window, in words
		);
		port(
			clk 			: in std_logic; -- Main clock ("small cycle" clock)
			sample_clk	: in std_logic; -- Sample clock ("large cycle" clock)
			data_in		: in std_logic_vector(data_width - 1 downto 0);			-- Data input
			data_out		: out std_logic_vector(data_width - 1 downto 0);		-- Data output
			address_out : in std_logic_vector(address_width - 1 downto 0);		-- Address for output data
			address_in	: in std_logic_vector(address_width - 1 downto 0);		-- Address for input data
			write_en		: in std_logic;			-- Write enable for writing data from data_in to address address_in
			rodata_out	: out std_logic_vector(data_width - 1 downto 0);		-- Read-only data output
			roaddress	: in std_logic_vector(address_width - 1 downto 0);		-- Address for the read-only data output
			mode			: in ringbuffer_mode	-- Buffer mode
		);
	end component;

	signal test_signal : std_logic;
begin
	input_buffer: ringbuffer
		generic map (
			data_width => data_width,
			address_width => 12 -- should be at least log2(buffer_size)
		)
		port map (
			clk => clk,
			sample_clk => sample_clk,
			data_in => (others => '0'),
			address_in => (others => '0'),
			address_out => (others => '0'),
			write_en => '0',
			roaddress => (others => '0'),
			mode => NORMAL_MODE
		);

	-- Instantiations

	process(clk)
	begin
		if rising_edge(clk) then
			test_signal <= '1';
		end if;
	end process;
end behaviour;
