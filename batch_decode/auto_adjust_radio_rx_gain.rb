


def adjust_radio_rx_gain()
  tstart = Time.now

  rxpa_max = '0x3000'

  rxpa_1 = '0x2000'
  rxpa_2 = '0x3000'

  rxgain_max = '0x1C00'
  rxgain_min_1 = '0x0100'
  rxgain_min_2 = '0x0200'

  rxgain_1 = '0x0200'
  rxgain_2 = '0x0100'

  while 1 do
    # sleep 120s
    #
    #

    10.times do
      rxgain_1 = rxgain_1.next
      rxgain_2 = rxgain_2.next
    end

    if rxgain_1 > rxgain_max or rxgain_2 > rxgain_max
      rxgain_1 = rxgain_min_1
      rxgain_2 = rxgain_min_2
    end

    system "dut rxgain --value #{rxgain_1} --radio 0"
    system "dut rxgain --value #{rxgain_2} --radio 1"

    puts "set rxgain: radio0=#{rxgain_1}, radio1=#{rxgain_2}"

    #
    tend = Time.now

    # time slice = 30min
    if tend - tstart > 60 * 30
      puts "reconfig radio...."

      system "configradio.cmd"

      tstart = Time.now
    end

    sleep 30
  end
end


adjust_radio_rx_gain()
