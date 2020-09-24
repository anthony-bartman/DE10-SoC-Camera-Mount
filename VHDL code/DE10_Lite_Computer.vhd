--Anthony Bartman
--Lab 5
--Dr. Livingston
--Summary:
--This creates a custom computer system that adds two servo's, a ADC joystick, 
--an accelerometer, and a camera to the computer system

--Servo1 Memory Address : 0xff20_0090 - 0xff20_009f
--Servo2 Memory Address : 0xff20_00a0 - 0xff20_00af
--Joystick Sequencer    : 0xff20_0210 - 0xff20_0217
--Joystick Sample Store : 0xff20_0400 - 0xff20_05ff
--Accelerometer			: 0xff20_00b0 - 0xff20_00b1
--Cam MEMORY ADDRESS		: 0xff20_00c0 - 0xff20_00ff

library ieee;
use ieee.std_logic_1164.all;

entity DE10_Lite_Computer is
port(
		-- Clock pins
		CLOCK_50 : in std_logic;
		CLOCK2_50 : in std_logic;
		CLOCK_ADC_10 : in std_logic;

		-- ARDUINO
		ARDUINO_IO : inout std_logic_vector(15 downto 0);
		ARDUINO_RESET_N : inout std_logic;
			
		-- SDRAM
		DRAM_ADDR : out std_logic_vector(12 downto 0);
		DRAM_BA : out std_logic_vector(1 downto 0);
		DRAM_CAS_N : out std_logic;
		DRAM_CKE : out std_logic;
		DRAM_CLK : out std_logic;
		DRAM_CS_N : out std_logic;
		DRAM_DQ : inout std_logic_vector(15 downto 0);
		DRAM_LDQM : out std_logic;
		DRAM_RAS_N : out std_logic;
		DRAM_UDQM : out std_logic;
		DRAM_WE_N : out std_logic;

		-- Accelerometer
		G_SENSOR_CS_N : out std_logic;
		G_SENSOR_INT : in std_logic_vector(2 downto 1);
		G_SENSOR_SCLK : out std_logic;
		G_SENSOR_SDI : inout std_logic;
		G_SENSOR_SDO : inout std_logic;
			
		-- 40-pin headers
		GPIO : inout std_logic_vector(35 downto 0);

		-- Seven Segment Displays
		HEX0 : out std_logic_vector(7 downto 0);
		HEX1 : out std_logic_vector(7 downto 0);
		HEX2 : out std_logic_vector(7 downto 0);
		HEX3 : out std_logic_vector(7 downto 0);
		HEX4 : out std_logic_vector(7 downto 0);
		HEX5 : out std_logic_vector(7 downto 0);

		-- Pushbuttons
		KEY : in std_logic_vector(1 downto 0);

		-- LEDs
		LEDR : out std_logic_vector(9 downto 0);

		-- Slider Switches
		SW : in std_logic_vector(9 downto 0);

		-- VGA
		VGA_B : out std_logic_vector(3 downto 0);
		VGA_G : out std_logic_vector(3 downto 0);
		VGA_HS : out std_logic;
		VGA_R : out std_logic_vector(3 downto 0);
		VGA_VS : out std_logic
		
		);
end entity DE10_Lite_Computer;


architecture Structural of DE10_Lite_Computer is

	component Computer_System is
        port (
            arduino_gpio_export        : inout std_logic_vector(15 downto 0) := (others => 'X'); -- export
            arduino_reset_n_export     : out   std_logic;                                        -- export
            expansion_jp1_export       : inout std_logic_vector(31 downto 0) := (others => 'X'); -- export
            hex3_hex0_export           : out   std_logic_vector(31 downto 0);                    -- export
            hex5_hex4_export           : out   std_logic_vector(15 downto 0);                    -- export
            leds_export                : out   std_logic_vector(9 downto 0);                     -- export
            pushbuttons_export         : in    std_logic_vector(1 downto 0)  := (others => 'X'); -- export
            sdram_addr                 : out   std_logic_vector(12 downto 0);                    -- addr
            sdram_ba                   : out   std_logic_vector(1 downto 0);                     -- ba
            sdram_cas_n                : out   std_logic;                                        -- cas_n
            sdram_cke                  : out   std_logic;                                        -- cke
            sdram_cs_n                 : out   std_logic;                                        -- cs_n
            sdram_dq                   : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
            sdram_dqm                  : out   std_logic_vector(1 downto 0);                     -- dqm
            sdram_ras_n                : out   std_logic;                                        -- ras_n
            sdram_we_n                 : out   std_logic;                                        -- we_n
            sdram_clk_clk              : out   std_logic;                                        -- clk
            slider_switches_export     : in    std_logic_vector(9 downto 0)  := (others => 'X'); -- export
            system_pll_ref_clk_clk     : in    std_logic                     := 'X';             -- clk
            system_pll_ref_reset_reset : in    std_logic                     := 'X';             -- reset
				servo_data1_export         : out   std_logic_vector(7 downto 0);                     -- export data
				servo_data2_export         : out   std_logic_vector(7 downto 0);                      -- export data
				accel_data_I2C_SDAT        : inout std_logic                     := 'X';             -- I2C_SDAT
            accel_data_I2C_SCLK        : out   std_logic;                                        -- I2C_SCLK
            accel_data_G_SENSOR_CS_N   : out   std_logic;                                        -- G_SENSOR_CS_N
            accel_data_G_SENSOR_INT    : in    std_logic                     := 'X';             -- G_SENSOR_INT	
 				cam_data_sda_in            : in    std_logic                     := 'X';             -- sda_in
            cam_data_scl_in            : in    std_logic                     := 'X';             -- scl_in
            cam_data_sda_oe            : out   std_logic;                                        -- sda_oe
            cam_data_scl_oe            : out   std_logic													    -- scl_oe
		  );
    end component Computer_System;
	 
	signal hex3_hex0 : std_logic_vector(31 downto 0);
	signal hex5_hex4 : std_logic_vector(15 downto 0);
	
	signal jp1_export : std_logic_vector(31 downto 0);
	signal keys : std_logic_vector(1 downto 0);
	signal dqm : std_logic_vector(1 downto 0);
	
	--Servos
	component SERVO is
	port(
			CLK : in std_logic;
			DATA : in std_logic_vector(7 downto 0);
			EN : out std_logic
		);
	end component SERVO;
	
	signal SERVO_DATA1 : std_logic_vector(7 downto 0); --Tells servos how to move
	signal SERVO_DATA2 : std_logic_vector(7 downto 0); --Tells servos how to move

	--Camera Components:
	--Pixel CLock/Slow clock
	component PIXELCLK is
	port(
			CLK : in std_logic;
			SL_CLK : out std_logic
		);
	end component PIXELCLK;
	
	--Used for slowing clock down
	signal X_CLK : std_logic;
	
	--I2c	
	signal SDA_IN : std_logic;
	signal SCL_IN : std_logic;
	signal SDA_OE : std_logic;
	signal SCL_OE : std_logic;
	
begin

	u0 : component Computer_System
        port map (
            arduino_gpio_export        => open,        			--         arduino_gpio.export
            arduino_reset_n_export     => open,     --      arduino_reset_n.export
            expansion_jp1_export       => jp1_export,      		--        expansion_jp1.export
            hex3_hex0_export           => hex3_hex0,           --            hex3_hex0.export
            hex5_hex4_export           => hex5_hex4,           --            hex5_hex4.export
            leds_export                => LEDR,                --                 leds.export
            pushbuttons_export         => keys,        			--          pushbuttons.export
            sdram_addr                 => DRAM_ADDR,           --                sdram.addr
            sdram_ba                   => DRAM_BA,             --                     .ba
            sdram_cas_n                => DRAM_CAS_N,          --                     .cas_n
            sdram_cke                  => DRAM_CKE,            --                     .cke
            sdram_cs_n                 => DRAM_CS_N,           --                     .cs_n
            sdram_dq                   => DRAM_DQ,             --                     .dq
            sdram_dqm                  => dqm,                 --                     .dqm
            sdram_ras_n                => DRAM_RAS_N,          --                     .ras_n
            sdram_we_n                 => DRAM_WE_N,           --                     .we_n
            sdram_clk_clk              => DRAM_CLK,            --            sdram_clk.clk
            slider_switches_export     => SW,    				   --      slider_switches.export
            system_pll_ref_clk_clk     => CLOCK_50,    			--   system_pll_ref_clk.clk
            system_pll_ref_reset_reset => '0',  					-- system_pll_ref_reset.reset
				servo_data1_export         => SERVO_DATA1,         --               servo1.export
				servo_data2_export         => SERVO_DATA2,         --               servo2.export
				accel_data_I2C_SDAT        => G_SENSOR_SDI, 			--           accel_data.I2C_SDAT
            accel_data_I2C_SCLK        => G_SENSOR_SCLK,       --                     .I2C_SCLK
            accel_data_G_SENSOR_CS_N   => G_SENSOR_CS_N,   		--                     .G_SENSOR_CS_N
            accel_data_G_SENSOR_INT    => open,    				--                     .G_SENSOR_INT
				cam_data_sda_in            => SDA_IN,            --             cam_data.sda_in
            cam_data_scl_in            => SCL_IN,            --                     .scl_in
            cam_data_sda_oe            => SDA_OE,            --                     .sda_oe
            cam_data_scl_oe            => SCL_OE				  --							 .scl_oe		
        );
		  
			HEX0 <= not hex3_hex0(7 downto 0);
			HEX1 <= not hex3_hex0(15 downto 8);
			HEX2 <= not hex3_hex0(23 downto 16);
			HEX3 <= not hex3_hex0(31 downto 24);
			HEX4 <= not hex5_hex4(7 downto 0);
			HEX5 <= not hex5_hex4(15 downto 8);

			GPIO(0) <= jp1_export(0);
			GPIO(15 downto 3) <= jp1_export(13 downto 1);
			GPIO(17) <= jp1_export(14);
			GPIO(35 downto 19) <= jp1_export(31 downto 15);
			
			keys <= not KEY;
			
			DRAM_UDQM <= dqm(1);
			DRAM_LDQM <= dqm(0);
	
	--Servos
	servo1 : component SERVO
			port map(
				CLK	=> CLOCK_50,
				DATA	=> SERVO_DATA1,
				EN => ARDUINO_IO(9)
				);
	servo2 : component SERVO
			port map(
				CLK	=> CLOCK_50,
				DATA	=> SERVO_DATA2,
				EN => ARDUINO_IO(10)
				);
				
	--Pixel Clock/Slow clock
	slowClock : component PIXELCLK
			port map(
				CLK => CLOCK_50,
				SL_CLK => X_CLK
			);
			
	--PIN 11 XCLK/slow clock
		ARDUINO_IO(11) <= X_CLK;
			
	--Camera Tri-State
		SCL_IN <= ARDUINO_IO(15); 
		ARDUINO_IO(15) <= '0' when SCL_OE = '1' else 'Z';
		SDA_IN <= ARDUINO_IO(14); 
		ARDUINO_IO(14) <= '0' when SDA_OE = '1' else 'Z';
		
	--Hardwires reset to be disabled for the camera
		ARDUINO_RESET_N <= '1';
	
end architecture;