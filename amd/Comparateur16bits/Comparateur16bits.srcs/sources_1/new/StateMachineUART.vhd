----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 10/04/2023 06:59:45 PM
-- Design Name: 
-- Module Name: StateMachineUART - Behavioral
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

entity StateMachineUART is
    Port ( CLK : in STD_LOGIC;
           RESET : in STD_LOGIC;
           Rx : in STD_LOGIC;
           ENABLE : in STD_LOGIC;
           Tx : out std_logic );
end StateMachineUART;

architecture Behavioral of StateMachineUART is

component rdc_8bits is
    Port ( RESET : in STD_LOGIC;
           CLK : in STD_LOGIC;
           INPUT : in STD_LOGIC;
           ENABLE : in STD_LOGIC;
           OUTPUT : out STD_LOGIC_VECTOR (7 downto 0));
end component;

component ADD_7bits is
    Port ( 
           clk : in STD_LOGIC;
           en : in STD_LOGIC;
           reset : in STD_LOGIC;
           S : out STD_LOGIC
           );
end component;

component Comparateur is
    Port ( A : in STD_LOGIC_VECTOR (7 downto 0);
           B : in STD_LOGIC_VECTOR (7 downto 0);
           C : out STD_LOGIC);
end component;

TYPE etats IS (Attente, Verification_Bit_De_Demarrage, Recuperer_Bits, Bit_De_Fin, Fin);
    SIGNAL etat_present : etats;
    SIGNAL etat_prochain : etats;
    SIGNAL Start_Bit,sC : std_logic :='1';
    SIGNAL OUTPUT_rdc : STD_LOGIC_VECTOR (7 downto 0);
    SIGNAL Donnees,sA,sB : STD_LOGIC_VECTOR (7 downto 0);
    SIGNAL EnCMP,SortieCMP : STD_LOGIC := '0';
    
    --Signaux Tx
    ---------Signals for baud rate--------
signal count : integer range 0 to 125000 := 0; --10416
signal flag : std_logic := '0';

------Signals for data tx---------
type state_type is (rdy,send_data,check_bit);
signal state :state_type := rdy;
signal txdata : std_logic_vector(9 downto 0);
signal tx_temp : std_logic;
signal bit_count : integer range 0 to 11 := 0;

    
    
    
    
begin

--rdc_8bits_i : rdc_8bits port map(RESET,CLK,RX,ENABLE,OUTPUT_rdc);
--ADD_7bits_i : ADD_7bits port map(CLK,EnCMP,RESET,SortieCMP);
--Comparateur_i_1 : Comparateur port map(sA,sB,sC);

BAUD_RATE_GENERATION_PROCESS : process(clk)
begin 
if(rising_edge(clk)) then
		if(state = rdy) then
			count <= 0;
		elsif(count < 125000) then	--wait till the baud rate completes to transmit the data --10416
			count <= count + 1;
			flag <= '0';
		else
			flag <= '1';
		end if;
end if;
end process;

DATA_TRANSMISSION_PROCESS : process(clk)
begin
if(rising_edge(clk))then
	case(state) is
	
		when rdy =>		--ready state of your ASM
		 tx_temp <= '1';
			if(ENABLE = '0') then
				state <= rdy;
			else
				state <= send_data;
				txdata <= ('1' & X"41" & '0');	--sending "A" on UART
			end if;
		when send_data =>
			tx_temp <= txdata(bit_count);
			bit_count <= bit_count + 1;
			state <= check_bit;
			
		when check_bit =>
			if(flag = '1') then 
				if(bit_count < 10) then
					state <=  send_data;
				else
					state <= rdy;
					bit_count <= 0;
				end if;
			else
				state <= check_bit;
			end if;
			 when others => state <= rdy;
	end case;
end if;
end process;

--Tx <= tx_temp;
Tx <= '1'; 


--125 MHz. Cette horloge est connectée à l'entrée K17 sur le FPGA, donc comme on a un baud rate de 9600
-- (125*10**6)/9600=2.60416667*10**4

--Start_Bit <= OUTPUT_rdc(0);

--    PROCESS (etat_present,Start_Bit)
--    BEGIN
--        CASE etat_present IS
--            WHEN Attente =>
--            if(Start_Bit = '0') then
--            etat_prochain <= Verification_Bit_De_Demarrage;
--            else
--            etat_prochain <= Attente;
--            end if;
--            WHEN Verification_Bit_De_Demarrage =>
--            etat_prochain <= Recuperer_Bits;
--            WHEN Recuperer_Bits =>
--            --wait pour 10-1 rising clk
--            Donnees(7 downto 0) <= OUTPUT_rdc(8 downto 1);
--            etat_prochain <= Bit_De_Fin;
--            WHEN Bit_De_Fin =>
            
--            if(OUTPUT_rdc(0) = '1') then
--            etat_prochain <= Fin;
--            else
--            etat_prochain <= Recuperer_Bits;
--            end if;
--            WHEN Fin =>
--            etat_prochain <= Attente;
--            WHEN OTHERS =>
--            etat_prochain <= etat_prochain;
--        end case;
--    END PROCESS;
    
    PROCESS (clk)
    BEGIN
        IF clk'EVENT AND clk = '1' THEN
            etat_present <= etat_prochain;
        END IF;
    END PROCESS;
    
end Behavioral;
