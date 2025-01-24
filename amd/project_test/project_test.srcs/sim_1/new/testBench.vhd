----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01/14/2025 03:00:23 PM
-- Design Name: 
-- Module Name: testBench - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity testBench is
--  Port ( );
end testBench;

architecture Behavioral of testBench is

component reg1bit is
    Port ( INPUT : in STD_LOGIC;
           OUTPUT : out STD_LOGIC;
           RESET : in STD_LOGIC;
           ENABLE : in STD_LOGIC;
           CLK : in STD_LOGIC);
end component;

signal INPUT : STD_LOGIC := '0';
signal OUTPUT : STD_LOGIC;
signal RESET : STD_LOGIC := '0';
signal ENABLE : STD_LOGIC := '0';
signal CLK : STD_LOGIC := '0';

begin

    UUT : reg1bit Port map ( INPUT, 
           OUTPUT,
           RESET,
           ENABLE, 
           CLK);

    process
    begin
        while true loop
            CLK <= '0';
            wait for 50 ns;
            CLK <= '1';
            wait for 50 ns;
        end loop;
    end process;

    process
    begin
        INPUT <= '0';
        RESET <= '0';
        ENABLE <= '0';
        wait for 50 us;
        INPUT <= '1';
        RESET <= '0';
        ENABLE <= '1';
        wait for 50 us;
        INPUT <= '1';
        RESET <= '1';
        ENABLE <= '0';
        wait for 50 us;
        INPUT <= '0';
        RESET <= '1';
        ENABLE <= '0';
        wait for 50 us;
        INPUT <= '0';
        RESET <= '1';
        ENABLE <= '0';
    end process;

end Behavioral;
