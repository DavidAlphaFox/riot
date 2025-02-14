open Core

module Timer : sig
  type t

  val pp : Format.formatter -> t -> unit
  val make : int64 -> [ `interval | `one_off ] -> (unit -> unit) -> t
  val equal : t -> t -> bool
end

type t

val create : unit -> t
val is_finished : t -> unit Ref.t -> bool
val remove_timer : t -> unit Ref.t -> unit
val extract_timer : t -> unit Ref.t -> Timer.t option
val add_timer : t -> Timer.t -> unit Ref.t

val make_timer :
  t -> int64 -> [ `interval | `one_off ] -> (unit -> unit) -> unit Ref.t

val clear_timer : t -> unit Ref.t -> unit
val tick : t -> unit
val can_tick : t -> bool
val size : t -> int
val move_timers : t -> t -> unit Ref.t list -> unit
