----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01/14/2025 02:29:05 PM
-- Design Name: 
-- Module Name: Reg1bit - Behavioral
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
-- use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
-- library UNISIM;
-- use UNISIM.VComponents.all;

entity Reg1bit is
    Port ( INPUT : in STD_LOGIC;
           OUTPUT : out STD_LOGIC;
           RESET : in STD_LOGIC;
           ENABLE : in STD_LOGIC;
           CLK : in STD_LOGIC);
end Reg1bit;

architecture Behavioral of Reg1bit is

signal a : STD_LOGIC := '0';

begin

Process(CLK)
begin
    if rising_edge(CLK) then
        if RESET = '1' then
            a <= '0';  -- Reset the register to 0
        elsif ENABLE = '1' then
            a <= INPUT;  -- Update register with input if ENABLE is high
        end if;
    end if;
end Process;

-- Assign the value of the buffer to the output
OUTPUT <= a;

end Behavioral;
