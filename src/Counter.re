// bellow commented maybe pattern to apply for timer id
// type timerOption = option(Js.Global.intervalId);

// let doSomething = (timerIdO: timerOption) =>
//   switch (timerIdO) {
//   | Some(timerId) => Js.log(timerId)
//   | None => ()
//   };

type state = {
  time: int,
  timerId: Js.Global.intervalId,
};

type action =
  | SetTimer(Js.Global.intervalId)
  | Tick;

let component = ReasonReact.reducerComponent("Counter");

let make = (~onFinish, ~initialTime=60, _children) => {
  ...component,

  initialState: () => {
    time: initialTime,
    timerId: Js.Global.setInterval(() => (), 1000),
  },

  reducer: action =>
    switch (action) {
    | SetTimer(timerId) => (state => ReasonReact.Update({...state, timerId}))
    | Tick => (
        state => {
          let updatedTime = state.time - 1;

          if (updatedTime == 0) {
            Js.Global.clearInterval(state.timerId);
            onFinish();
          };

          ReasonReact.Update({...state, time: updatedTime});
        }
      )
    },

  didMount: ({send}) => {
    let intervalId = Js.Global.setInterval(() => send(Tick), 1000);
    send(SetTimer(intervalId));
  },

  willUnmount: ({state: {timerId}}) => Js.Global.clearInterval(timerId),

  render: ({state: {time}}) =>
    <div> {ReasonReact.string("Time left: " ++ string_of_int(time))} </div>,
};