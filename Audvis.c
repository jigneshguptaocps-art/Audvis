module i2s_tx #(
    parameter int unsigned CLK_HZ = 100_000_000,
    parameter int unsigned SAMPLE_HZ = 48_000, 
    parameter int unsigned SAMPLE_W = 16,
    parameter int unsigned CHNL_CNT = 2
)(
    input logic clk_i,
    input logic rst_ni,
    input logic enable_i, 

    //Sample steam input (from audio_dma)
    input logic [SAMPLE_W-1:0] sample_i,
    input logic sample_valid_i,
    output logic sample_ready_o,

    //I2S output 
    output logic i2s_sdata_o,
    output logic i2s_bclk_o,
    output logic i2s_lrclk_o, 


    //Status / interrupts 
    output logic underrun_o,
    output logic irq_o
);

localparam int unsigned BCLK_HZ = SAMPLE_HZ * CHNL_CNT * SAMPLE_W;
localparam int unsigned LRCLK_HZ = SAMPLE_HZ;
localparam int unsigned BCLK_TOGGLE = 2 * BCLK_HZ; 
localparam int unsigned DIV = CLK_HZ / (2 * BCLK_HZ);

//clock generation and timing
logic bclk_q; 
logic lrclk_q;
logic [8:0] div_cnt_q; 
logic bclk_rise;
logic bclk_fall;
logic bclk_fall_q; 
logic [3:0] bit_idx_q; 
logic channel_q; 

//sample bufferinf (valid/ready)
logic [SAMPLE_W-1:0] samp_buf_q; 
logic have_buf_q; 

//shift engine 
logic [SAMPLE_W-1:0] shreg_q;
logic sdata_q;

//staus / interrupts
logic underrun_q;
logic irq_q; 

//state machine logic 
typedef enum logic [2:0] { 
    IDLE,
    LOAD,
    SHIFT,
    ERROR
} state_e;

state_e state_q, state_d; 
//state variable reset and initalization 
always_ff @(posedge clk_i or negedge rst_ni) begin
    if (!rst_ni) begin
        state_q <= IDLE;
    end else begin
        state_q <= state_d; 
    end
end

always_comb begin
    state_d = state_q;
    case (state_q)
        IDLE: begin 
            if (enable_i) begin

                state_d = LOAD; 
            end
        end 
        LOAD: begin
            if (bclk_fall) begin
                state_d = SHIFT;
            end 
        end
        SHIFT: begin
            if (bclk_fall && (bit_idx_q == SAMPLE_W - 1)) begin
                state_d = LOAD; 
            end
        end
        ERROR: begin
            state_d = IDLE; 
        end 
        default: state_d = IDLE;  
    endcase 
end

assign sample_ready_o = enable_i && !have_buf_q;

always_ff @(posedge clk_i or negedge rst_ni) begin
... (76 lines left)