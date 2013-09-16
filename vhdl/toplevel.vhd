-- Superawesome Project Processor
library ieee;
use ieee.std_logic_1164.ALL;

library work;
use work.core_constants.all;

entity toplevel is
	-- These ports connect to pins on the FPGA. These are set up using PlanAhead
	-- and stored in a .ucf file. This must be done sometime later.

	port (
		clk : in std_logic; -- "Small cycle" clock, i.e. processor core clock
		sample_clk : in std_logic; -- "Large cycle" clock, i.e. sample clock

		-- EBI interface lines:
		ebi_address : in std_logic_vector(27 downto 0);	-- EBI address lines
		ebi_data		: in std_logic_vector(15 downto 0); -- EBI data lines
		ebi_re		: in std_logic;	-- EBI read enable (active low)
		ebi_we		: in std_logic;	-- EBI write enable (active low)
		ebi_cs		: in std_logic		-- EBI chip select (active low)
	);
end entity;

architecture behaviour of toplevel is
	component pipeline is
		generic (
			address_width	: natural := 28;
			data_width		: natural := 16;
			num_cores		: natural := 4
		);
		port (
			clk			: in std_logic;	-- Small cycle clock
			sample_clk	: in std_logic;	-- Large cucle clock

			address	: in std_logic_vector(address_width - 1 downto 0);
			data		: in std_logic_vector(data_width - 1 downto 0);
			write_en	: in std_logic
		);
	end component;
begin

	-- Create a predefined number of pipelines
	-- TODO: connect them to an EBI interface module
	-- TODO: give the pipelines their own address bases, maybe through generics?
	generate_pipelines:
	for pl in 0 to NUMBER_OF_PIPELINES - 1 generate
		pipeline_x: pipeline
			port map (
				clk => clk,
				sample_clk => sample_clk,
				address => (others => '0'),
				data => (others => '0'),
				write_en => '0'
			);
	end generate generate_pipelines;

end behaviour;
