IFACE=wlp0s20f3

while true; do
  RX1=$(cat /sys/class/net/$IFACE/statistics/rx_bytes)
  TX1=$(cat /sys/class/net/$IFACE/statistics/tx_bytes)

  sleep 2

  RX2=$(cat /sys/class/net/$IFACE/statistics/rx_bytes)
  TX2=$(cat /sys/class/net/$IFACE/statistics/tx_bytes)

  RX=$((RX2 - RX1))
  TX=$((TX2 - TX1))

  echo "↓ $((RX / 1024))K/s ↑ $((TX / 1024))K/s"
done
