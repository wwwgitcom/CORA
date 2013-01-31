require 'net/http'


def adjust_ap_data_rate()
  tstart = Time.now

  rate_min = 8
  rate_max = 14

  rate_now = 8

  uri = URI('http://192.168.1.10/confirm.asp')

  while 1 do
    begin
      res = Net::HTTP.post_form(uri, 
       'q' => 'ruby', 'max' => '50'
      )

      puts res.body
    rescue Exception => e
      puts "Exception............"
      puts e
    end

    rate_now += 1

    if rate_now > rate_max
      rate_now = rate_min
    end

    # change rate / 5min
    sleep 60 * 5
  end
end


adjust_ap_data_rate()

