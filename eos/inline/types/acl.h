// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_ACL_H
#define EOS_INLINE_TYPES_ACL_H

namespace eos {

// Default constructor.
inline acl_ttl_spec_t::acl_ttl_spec_t() :
      oper_(ACL_RANGE_ANY), ttl_(0) {
}

// Constructor for different ttl specs, note if oper is ACL_RANGE_ANY, the ttl
// should be set to 0.
inline acl_ttl_spec_t::acl_ttl_spec_t(acl_range_operator_t oper, uint8_t ttl) :
      oper_(oper), ttl_(ttl) {
}

inline acl_range_operator_t
acl_ttl_spec_t::oper() const {
   return oper_;
}

inline void
acl_ttl_spec_t::oper_is(acl_range_operator_t oper) {
   oper_ = oper;
}

inline uint8_t
acl_ttl_spec_t::ttl() const {
   return ttl_;
}

inline void
acl_ttl_spec_t::ttl_is(uint8_t ttl) {
   ttl_ = ttl;
}

inline bool
acl_ttl_spec_t::operator==(acl_ttl_spec_t const & other) const {
   return oper_ == other.oper_ &&
          ttl_ == other.ttl_;
}

inline bool
acl_ttl_spec_t::operator!=(acl_ttl_spec_t const & other) const {
   return !operator==(other);
}

inline std::string
acl_ttl_spec_t::to_string() const {
   std::ostringstream ss;
   ss << "acl_ttl_spec_t(";
   ss << "oper=" << oper_;
   ss << ", ttl=" << ttl_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const acl_ttl_spec_t& obj) {
   os << obj.to_string();
   return os;
}



inline acl_port_spec_t::acl_port_spec_t() :
      oper_(ACL_RANGE_ANY), ports_() {
}

inline acl_port_spec_t::acl_port_spec_t(acl_range_operator_t oper, 
                                 std::list<uint16_t> const & ports) :
      oper_(oper) {
   for (std::list<uint16_t>::const_iterator pit = ports.cbegin();
        pit != ports.cend(); ++pit) {
        ports_.push_back(*pit);
   }
   
}

inline acl_range_operator_t
acl_port_spec_t::oper() const {
   return oper_;
}

inline void
acl_port_spec_t::oper_is(acl_range_operator_t oper) {
   oper_ = oper;
}

inline std::list<uint16_t> const &
acl_port_spec_t::ports() const {
   return ports_;
}

inline void
acl_port_spec_t::ports_is(std::list<uint16_t> const & ports) {
   ports_ = ports;
}

inline void
acl_port_spec_t::port_set(uint16_t const & ports) {
   ports_.push_front(ports);
}

inline void
acl_port_spec_t::port_del(uint16_t const & ports) {
   ports_.remove(ports);
}

inline bool
acl_port_spec_t::operator==(acl_port_spec_t const & other) const {
   return oper_ == other.oper_ &&
          ports_ == other.ports_;
}

inline bool
acl_port_spec_t::operator!=(acl_port_spec_t const & other) const {
   return !operator==(other);
}

inline std::string
acl_port_spec_t::to_string() const {
   std::ostringstream ss;
   ss << "acl_port_spec_t(";
   ss << "oper=" << oper_;
   ss << ", ports=" <<"'";
   bool first_ports = true;
   for (auto it=ports_.cbegin(); it!=ports_.cend(); ++it) {
      if (first_ports) {
         ss << (*it);
         first_ports = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const acl_port_spec_t& obj) {
   os << obj.to_string();
   return os;
}



inline acl_port_spec_t
get_acl_port_spec_eq(uint16_t port) {
   std::list<uint16_t> l = { port };
   return acl_port_spec_t( ACL_RANGE_EQ, l );
}


inline acl_port_spec_t
get_acl_port_spec_eq(std::list<uint16_t> const & ports) {
   return acl_port_spec_t( ACL_RANGE_EQ, ports );
}


inline acl_port_spec_t
get_acl_port_spec_neq(uint16_t port) {
   std::list<uint16_t> l = { port };
   return acl_port_spec_t( ACL_RANGE_NEQ, l );
}


inline acl_port_spec_t
get_acl_port_spec_neq(std::list<uint16_t> const & ports) {
   return acl_port_spec_t( ACL_RANGE_NEQ, ports );
}


inline acl_port_spec_t
get_acl_port_spec_between(uint16_t low, uint16_t high) {
   std::list<uint16_t> l = { low, high };
   return acl_port_spec_t( ACL_RANGE_BETWEEN, l );
}


inline acl_port_spec_t
get_acl_port_spec_gt(uint16_t port) {
   std::list<uint16_t> l = { port };
   return acl_port_spec_t( ACL_RANGE_GT, l );
}


inline acl_port_spec_t
get_acl_port_spec_lt(uint16_t port) {
   std::list<uint16_t> l = { port };
   return acl_port_spec_t( ACL_RANGE_LT, l );
}


inline acl_port_spec_t
get_acl_port_spec_any() {
   return acl_port_spec_t();
}


inline acl_key_t::acl_key_t() :
      acl_name_(), acl_type_(ACL_TYPE_NULL) {
}

inline acl_key_t::acl_key_t(std::string const & acl_name, acl_type_t acl_type) :
      acl_name_(acl_name), acl_type_(acl_type) {
}

inline std::string
acl_key_t::acl_name() const {
   return acl_name_;
}

inline acl_type_t
acl_key_t::acl_type() const {
   return acl_type_;
}

inline bool
acl_key_t::operator()(acl_key_t const & lhs, acl_key_t const & rhs) const {
   return lhs.acl_name_ < rhs.acl_name_;
}

inline bool
acl_key_t::operator==(acl_key_t const & other) const {
   return acl_name_ == other.acl_name_ &&
          acl_type_ == other.acl_type_;
}

inline bool
acl_key_t::operator!=(acl_key_t const & other) const {
   return !operator==(other);
}

inline std::string
acl_key_t::to_string() const {
   std::ostringstream ss;
   ss << "acl_key_t(";
   ss << "acl_name='" << acl_name_ << "'";
   ss << ", acl_type=" << acl_type_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const acl_key_t& obj) {
   os << obj.to_string();
   return os;
}



inline acl_rule_base_t::acl_rule_base_t() :
   action_(ACL_PERMIT), log_(false), tracked_(false) {
}

inline acl_action_t
acl_rule_base_t::action() const {
   return action_;
}

inline void
acl_rule_base_t::action_is(acl_action_t action) {
   action_ = action;
}

inline bool
acl_rule_base_t::log() const {
   return log_;
}

inline void
acl_rule_base_t::log_is(bool log) {
   log_ = log;
}

inline bool
acl_rule_base_t::tracked() const {
   return tracked_;
}

inline void
acl_rule_base_t::tracked_is(bool tracked) {
   tracked_ = tracked;
}

inline std::string
acl_rule_base_t::to_string() const {
   std::ostringstream ss;
   ss << "acl_rule_base_t(";
   ss << "action=" << action_;
   ss << ", log=" << log_;
   ss << ", tracked=" << tracked_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const acl_rule_base_t& obj) {
   os << obj.to_string();
   return os;
}



// Constructor for concrete rule ip type passed to acl_add_rule() variants.
inline acl_rule_ip_t::acl_rule_ip_t() :
      vlan_(), vlan_mask_(0xFFF), inner_vlan_(), inner_vlan_mask_(0xFFF), ip_protocol_(), 
      ttl_(), source_addr_(), destination_addr_(), source_port_(), destination_port_(), 
      tcp_flags_(), established_(), icmp_type_(ALL_ICMP), icmp_code_(ALL_ICMP), 
      priority_value_(), priority_mask_(), match_fragments_(), match_ip_priority_() {
}

inline vlan_id_t
acl_rule_ip_t::vlan() const {
   return vlan_;
}

inline void
acl_rule_ip_t::vlan_is(vlan_id_t vlan) {
   vlan_ = vlan;
}

inline vlan_id_t
acl_rule_ip_t::vlan_mask() const {
   return vlan_mask_;
}

inline void
acl_rule_ip_t::vlan_mask_is(vlan_id_t vlan_mask) {
   vlan_mask_ = vlan_mask;
}

inline vlan_id_t
acl_rule_ip_t::inner_vlan() const {
   return inner_vlan_;
}

inline void
acl_rule_ip_t::inner_vlan_is(vlan_id_t inner_vlan) {
   inner_vlan_ = inner_vlan;
}

inline vlan_id_t
acl_rule_ip_t::inner_vlan_mask() const {
   return inner_vlan_mask_;
}

inline void
acl_rule_ip_t::inner_vlan_mask_is(vlan_id_t inner_vlan_mask) {
   inner_vlan_mask_ = inner_vlan_mask;
}

inline uint8_t
acl_rule_ip_t::ip_protocol() const {
   return ip_protocol_;
}

inline void
acl_rule_ip_t::ip_protocol_is(uint8_t ip_protocol) {
   ip_protocol_ = ip_protocol;
}

inline acl_ttl_spec_t
acl_rule_ip_t::ttl() const {
   return ttl_;
}

inline void
acl_rule_ip_t::ttl_is(acl_ttl_spec_t ttl) {
   ttl_ = ttl;
}

inline ip_addr_mask_t
acl_rule_ip_t::source_addr() const {
   return source_addr_;
}

inline void
acl_rule_ip_t::source_addr_is(ip_addr_mask_t const & source_addr) {
   source_addr_ = source_addr;
}

inline ip_addr_mask_t
acl_rule_ip_t::destination_addr() const {
   return destination_addr_;
}

inline void
acl_rule_ip_t::destination_addr_is(ip_addr_mask_t const & destination_addr) {
   destination_addr_ = destination_addr;
}

inline acl_port_spec_t
acl_rule_ip_t::source_port() const {
   return source_port_;
}

inline void
acl_rule_ip_t::source_port_is(acl_port_spec_t source_port) {
   source_port_ = source_port;
}

inline acl_port_spec_t
acl_rule_ip_t::destination_port() const {
   return destination_port_;
}

inline void
acl_rule_ip_t::destination_port_is(acl_port_spec_t destination_port) {
   destination_port_ = destination_port;
}

inline uint16_t
acl_rule_ip_t::tcp_flags() const {
   return tcp_flags_;
}

inline void
acl_rule_ip_t::tcp_flags_is(uint16_t tcp_flags) {
   tcp_flags_ = tcp_flags;
}

inline bool
acl_rule_ip_t::established() const {
   return established_;
}

inline void
acl_rule_ip_t::established_is(bool established) {
   established_ = established;
}

inline uint16_t
acl_rule_ip_t::icmp_type() const {
   return icmp_type_;
}

inline void
acl_rule_ip_t::icmp_type_is(uint16_t icmp_type) {
   icmp_type_ = icmp_type;
}

inline uint16_t
acl_rule_ip_t::icmp_code() const {
   return icmp_code_;
}

inline void
acl_rule_ip_t::icmp_code_is(uint16_t icmp_code) {
   icmp_code_ = icmp_code;
}

inline uint8_t
acl_rule_ip_t::priority_value() const {
   return priority_value_;
}

inline void
acl_rule_ip_t::priority_value_is(uint8_t priority_value) {
   priority_value_ = priority_value;
}

inline uint8_t
acl_rule_ip_t::priority_mask() const {
   return priority_mask_;
}

inline void
acl_rule_ip_t::priority_mask_is(uint8_t priority_mask) {
   priority_mask_ = priority_mask;
}

inline bool
acl_rule_ip_t::match_fragments() const {
   return match_fragments_;
}

inline void
acl_rule_ip_t::match_fragments_is(bool match_fragments) {
   match_fragments_ = match_fragments;
}

inline bool
acl_rule_ip_t::match_ip_priority() const {
   return match_ip_priority_;
}

inline void
acl_rule_ip_t::match_ip_priority_is(bool match_ip_priority) {
   match_ip_priority_ = match_ip_priority;
}

inline bool
acl_rule_ip_t::operator==(acl_rule_ip_t const & other) const {
   return vlan_ == other.vlan_ &&
          vlan_mask_ == other.vlan_mask_ &&
          inner_vlan_ == other.inner_vlan_ &&
          inner_vlan_mask_ == other.inner_vlan_mask_ &&
          ip_protocol_ == other.ip_protocol_ &&
          ttl_ == other.ttl_ &&
          source_addr_ == other.source_addr_ &&
          destination_addr_ == other.destination_addr_ &&
          source_port_ == other.source_port_ &&
          destination_port_ == other.destination_port_ &&
          tcp_flags_ == other.tcp_flags_ &&
          established_ == other.established_ &&
          icmp_type_ == other.icmp_type_ &&
          icmp_code_ == other.icmp_code_ &&
          priority_value_ == other.priority_value_ &&
          priority_mask_ == other.priority_mask_ &&
          match_fragments_ == other.match_fragments_ &&
          match_ip_priority_ == other.match_ip_priority_;
}

inline bool
acl_rule_ip_t::operator!=(acl_rule_ip_t const & other) const {
   return !operator==(other);
}

inline std::string
acl_rule_ip_t::to_string() const {
   std::ostringstream ss;
   ss << "acl_rule_ip_t(";
   ss << "vlan=" << vlan_;
   ss << ", vlan_mask=" << vlan_mask_;
   ss << ", inner_vlan=" << inner_vlan_;
   ss << ", inner_vlan_mask=" << inner_vlan_mask_;
   ss << ", ip_protocol=" << ip_protocol_;
   ss << ", ttl=" << ttl_;
   ss << ", source_addr=" << source_addr_.to_string();
   ss << ", destination_addr=" << destination_addr_.to_string();
   ss << ", source_port=" << source_port_;
   ss << ", destination_port=" << destination_port_;
   ss << ", tcp_flags=" << tcp_flags_;
   ss << ", established=" << established_;
   ss << ", icmp_type=" << icmp_type_;
   ss << ", icmp_code=" << icmp_code_;
   ss << ", priority_value=" << priority_value_;
   ss << ", priority_mask=" << priority_mask_;
   ss << ", match_fragments=" << match_fragments_;
   ss << ", match_ip_priority=" << match_ip_priority_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const acl_rule_ip_t& obj) {
   os << obj.to_string();
   return os;
}



inline acl_rule_eth_t::acl_rule_eth_t() :
      vlan_(), vlan_mask_(0xFFF), inner_vlan_(), inner_vlan_mask_(0xFFF), source_addr_(), 
      destination_addr_(), source_mask_(), destination_mask_() {
}

inline vlan_id_t
acl_rule_eth_t::vlan() const {
   return vlan_;
}

inline void
acl_rule_eth_t::vlan_is(vlan_id_t vlan) {
   vlan_ = vlan;
}

inline vlan_id_t
acl_rule_eth_t::vlan_mask() const {
   return vlan_mask_;
}

inline void
acl_rule_eth_t::vlan_mask_is(vlan_id_t vlan_mask) {
   vlan_mask_ = vlan_mask;
}

inline vlan_id_t
acl_rule_eth_t::inner_vlan() const {
   return inner_vlan_;
}

inline void
acl_rule_eth_t::inner_vlan_is(vlan_id_t inner_vlan) {
   inner_vlan_ = inner_vlan;
}

inline vlan_id_t
acl_rule_eth_t::inner_vlan_mask() const {
   return inner_vlan_mask_;
}

inline void
acl_rule_eth_t::inner_vlan_mask_is(vlan_id_t inner_vlan_mask) {
   inner_vlan_mask_ = inner_vlan_mask;
}

inline eth_addr_t
acl_rule_eth_t::source_addr() const {
   return source_addr_;
}

inline void
acl_rule_eth_t::source_addr_is(eth_addr_t const & source_addr) {
   source_addr_ = source_addr;
}

inline eth_addr_t
acl_rule_eth_t::destination_addr() const {
   return destination_addr_;
}

inline void
acl_rule_eth_t::destination_addr_is(eth_addr_t const & destination_addr) {
   destination_addr_ = destination_addr;
}

inline eth_addr_t
acl_rule_eth_t::source_mask() const {
   return source_mask_;
}

inline void
acl_rule_eth_t::source_mask_is(eth_addr_t const & source_mask) {
   source_mask_ = source_mask;
}

inline eth_addr_t
acl_rule_eth_t::destination_mask() const {
   return destination_mask_;
}

inline void
acl_rule_eth_t::destination_mask_is(eth_addr_t const & destination_mask) {
   destination_mask_ = destination_mask;
}

inline bool
acl_rule_eth_t::operator==(acl_rule_eth_t const & other) const {
   return vlan_ == other.vlan_ &&
          vlan_mask_ == other.vlan_mask_ &&
          inner_vlan_ == other.inner_vlan_ &&
          inner_vlan_mask_ == other.inner_vlan_mask_ &&
          source_addr_ == other.source_addr_ &&
          destination_addr_ == other.destination_addr_ &&
          source_mask_ == other.source_mask_ &&
          destination_mask_ == other.destination_mask_;
}

inline bool
acl_rule_eth_t::operator!=(acl_rule_eth_t const & other) const {
   return !operator==(other);
}

inline std::string
acl_rule_eth_t::to_string() const {
   std::ostringstream ss;
   ss << "acl_rule_eth_t(";
   ss << "vlan=" << vlan_;
   ss << ", vlan_mask=" << vlan_mask_;
   ss << ", inner_vlan=" << inner_vlan_;
   ss << ", inner_vlan_mask=" << inner_vlan_mask_;
   ss << ", source_addr=" << source_addr_.to_string();
   ss << ", destination_addr=" << destination_addr_.to_string();
   ss << ", source_mask=" << source_mask_.to_string();
   ss << ", destination_mask=" << destination_mask_.to_string();
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const acl_rule_eth_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_ACL_H