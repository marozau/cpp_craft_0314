require 'socket'
require_relative 'cta_sender_helper'

class CTA_sender
  
  def initialize( multicast_addrs_ports, real_time = true )
    @multicast_addrs_ports = multicast_addrs_ports
    @real_time = real_time
    find_multicast_data
  end

  def find_multicast_data
    @file_names = []
    @multicast_addrs_ports.each do |index, address|
      file_path = "#{address[0]}.udp"
      @file_names << file_path if File.exists? file_path
    end 
    puts 'no multicast data' if @file_names.empty?		
  end

  def start
    sended_messages = 0;
    while true
      @file_names.each do |file_name|
        f = File.open( file_name, "rb" )
        begin
          socket = UDPSocket.open
          socket.setsockopt(Socket::IPPROTO_IP, Socket::IP_TTL, [1].pack('i'))
          line_c = 0
          while (!f.eof?)
            while (line_c < 100)
              line = f.readline
              line_c = line_c + 1
            end
            line = f.readline
            if @real_time
              write_time line
              write_index line, sended_messages
            end
            i = (rand()*(@multicast_addrs_ports.size - 1)).round + 1
            socket.send(line, 0, @multicast_addrs_ports[i][0], @multicast_addrs_ports[i][1])
            sended_messages+=1
          end
        ensure
          socket.close 
        end
        f.close
      end    
    end
  end
end

